/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pre.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:00:00 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/25 13:39:11 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Counts the number of heredocs in a token list
 * @param token Starting token in list
 * @return Number of heredocs found
 */
int	count_heredocs(t_token *token)
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
 * @brief Allocates memory for heredoc tokens and file descriptors
 * @param mini Shell state
 * @param count Number of heredocs
 * @return 0 on success, 1 on failure
 */
int	allocate_heredoc_arrays(t_mini *mini, int count)
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
 * @brief Processes a single heredoc
 * @param mini Shell state
 * @param current Current heredoc token
 * @param i Index in heredoc arrays
 * @return 0 on success, 1 on failure
 */
int	process_single_heredoc(t_mini *mini, t_token *current, int i)
{
	char	*delimiter;

	delimiter = get_heredoc_delimiter(current);
	if (!delimiter)
		return (1);
	mini->heredoc_tokens[i] = current;
	mini->heredoc_fds[i] = here_doc_with_num(mini, delimiter, i + 1);
	if (mini->heredoc_fds[i] == -1)
		return (1);
	current->processed = TRUE;
	return (0);
}
