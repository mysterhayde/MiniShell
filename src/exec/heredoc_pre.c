/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pre.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:00:00 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/24 13:24:17 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Counts the number of heredocs in a token list
 * @param token Starting token in list
 * @return Number of heredocs found
 */
static int	count_heredocs(t_token *token)
{
	t_token	*current;
	int		count;

	count = 0;
	current = token;
	while (current)
	{
		if (current->type == HERE_DOC && current->next)
			count++;
		current = current->next;
	}
	return (count);
}

/**
 * @brief Allocates memory for heredoc tokens and file descriptors
 * @param mini Shell state
 * @param count Number of heredocs
 * @return 0 on success, 1 on failure
 */
static int	allocate_heredoc_arrays(t_mini *mini, int count)
{
	if (count <= 0)
		return (0);
	mini->heredoc_count = count;
	mini->heredoc_tokens = malloc(sizeof(t_token *) * count);
	if (!mini->heredoc_tokens)
		return (1);
	mini->heredoc_fds = malloc(sizeof(int) * count);
	if (!mini->heredoc_fds)
	{
		free(mini->heredoc_tokens);
		mini->heredoc_tokens = NULL;
		return (1);
	}
	return (0);
}

/**
 * @brief Gets the delimiter for a heredoc token
 * @param token Heredoc token
 * @return Delimiter string or NULL on error
 */
static char	*get_heredoc_delimiter(t_token *token)
{
	if (!token || !token->next)
		return (NULL);
	return (token->next->cmd[0]);
}

/**
 * @brief Executes all heredocs and stores file descriptors
 * @param mini Shell state
 * @return 0 on success, 1 on failure
 */
static int	execute_heredocs(t_mini *mini)
{
	t_token	*current;
	char	*delimiter;
	int		i;

	current = mini->token;
	i = 0;
	while (current && i < mini->heredoc_count)
	{
		if (current->type == HERE_DOC && current->next)
		{
			delimiter = get_heredoc_delimiter(current);
			if (!delimiter)
				return (1);
			mini->heredoc_tokens[i] = current;
			mini->heredoc_fds[i] = here_doc_with_num(delimiter, i + 1);
			if (mini->heredoc_fds[i] == -1)
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