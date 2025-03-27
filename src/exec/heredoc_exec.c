/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:12:53 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/27 22:31:06 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Executes all heredocs and stores file descriptors
 * @param mini Shell state
 * @return 0 on success, 1 on failure
 */
static int	execute_heredocs(t_mini *mini)
{
	t_token	*current;
	int		i;

	current = mini->token;
	i = 0;
	while (current && i < mini->heredoc_count)
	{
		if (current->type == HERE_DOC && current->next && !current->processed)
		{
			if (process_single_heredoc(mini, current, i))
				return (1);
			i++;
		}
		current = current->next;
	}
	return (0);
}

/**
 * @brief Scans and executes all heredocs in the command line
 * @param mini Shell state
 * @return 0 on success, 1 on failure
 */
int	scan_and_execute_heredocs(t_mini *mini)
{
	int	count;
	int	result;

	if (!mini || !mini->token)
		return (0);
	count = count_heredocs(mini->token);
	if (count == 0)
		return (0);
	if (allocate_heredoc_arrays(mini, count))
		return (1);
	mini->isheredoc = TRUE;
	result = execute_heredocs(mini);
	mini->isheredoc = FALSE;
	if (result)
	{
		free_heredoc_arrays(mini);
		return (1);
	}
	return (0);
}
