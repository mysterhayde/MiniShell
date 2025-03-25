/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:32:00 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/25 13:33:21 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Marks all heredoc tokens in a token list as processed
 * @param token Starting token
 */
static void	mark_all_heredocs_processed(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == HERE_DOC)
			current->processed = TRUE;
		current = current->next;
	}
}

/**
 * @brief Scans for heredocs in a token list including after logical operators
 * @param token Starting token
 * @return Number of heredocs found
 */
static int	count_all_heredocs(t_token *token)
{
	t_token	*current;
	int		count;

	count = 0;
	current = token;
	while (current)
	{
		if (current->type == HERE_DOC && current->next && !current->processed)
			count++;
		current = current->next;
	}
	return (count);
}

/**
 * @brief Executes all heredocs in the entire command line
 * @param mini Shell state
 * @return 0 on success, 1 on failure
 */
static int	execute_all_heredocs(t_mini *mini)
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
 * @brief Scans and executes all heredocs in the entire command line
 * @param mini Shell state
 * @return 0 on success, 1 on failure
 */
int	scan_and_execute_all_heredocs(t_mini *mini)
{
	int	count;
	int	result;

	if (!mini || !mini->token)
		return (0);
	reset_heredoc_processed_flags(mini->token);
	count = count_all_heredocs(mini->token);
	if (count == 0)
		return (0);
	if (allocate_heredoc_arrays(mini, count))
		return (1);
	mini->isheredoc = TRUE;
	result = execute_all_heredocs(mini);
	mini->isheredoc = FALSE;
	if (result)
	{
		free_heredoc_arrays(mini);
		return (1);
	}
	mark_all_heredocs_processed(mini->token);
	free_heredoc_arrays(mini);
	return (0);
}
