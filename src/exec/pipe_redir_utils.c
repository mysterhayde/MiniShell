/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:05:35 by cbopp             #+#    #+#             */
/*   Updated: 2025/04/06 14:41:18 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Checks if a redirection token i for output
 * @param token Redirection token
 * @return TRUE if output redirection, FALSE otherwise
 */
t_bool	is_output_redir(t_token *token)
{
	if (token->type == RDIT && token->cmd && token->cmd[0])
	{
		if (ft_strmincmp(token->cmd[0], ">", 1) == 0
			|| ft_strmincmp(token->cmd[0], ">>", 2) == 0)
			return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief Applies redirections up to the next pipe with heredoc support
 * @param mini Shell state
 * @param token STarting token
 * @param is_last_cmd Flag indicating if this is the last command in pipeline
 * @return 0 on success, 1 on failure
 */
int	apply_pipe_redir_with_heredoc(t_mini *mini, t_token *token,
	t_bool is_last_cmd)
{
	t_token	*current;
	t_token	*next_pipe;

	current = token;
	next_pipe = find_next_pipe_token(token);
	while (current && current != next_pipe)
	{
		if (((current->type == RDIT && current->next
					&& current->next->type == FILES)
				|| current->type == HERE_DOC) && current->next)
		{
			if (current->type == HERE_DOC
				|| !is_output_redir(current)
				|| (is_last_cmd && is_output_redir(current)))
			{
				if (process_single_redir_with_heredoc(mini, current))
					return (1);
			}
		}
		current = current->next;
	}
	return (0);
}
