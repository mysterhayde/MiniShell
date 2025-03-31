/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:55:27 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/31 11:46:08 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Determine if a token is only for the last command in a pipeline
 * @param token Token to check
 * @param is_last_cmd Flag indicating if current command is last in pipeline
 * @return TRUE if should be skipped, FALSE otherwise
 */
t_bool	should_skip_token(t_token *token, t_bool is_last_cmd)
{
	if (!is_last_cmd && token->type == RDIT && token->cmd && token->cmd[0])
	{
		if (ft_strmincmp(token->cmd[0], ">", 1) == 0
			|| ft_strmincmp(token->cmd[0], ">>", 2) == 0)
			return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief Mark tokens that should only be processed by the last command
 * @param token Starting token
 * @return None
 */
void	mark_last_command_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == RDIT && current->cmd && current->cmd[0])
		{
			if (ft_strmincmp(current->cmd[0], ">", 1) == 0
				|| ft_strmincmp(current->cmd[0], ">>", 2) == 0)
				current->processed = TRUE;
			else
				current->processed = FALSE;
		}
		else
			current->processed = FALSE;
		current = current->next;
	}
}
