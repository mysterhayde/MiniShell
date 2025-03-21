/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_post.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:27:45 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/21 13:37:38 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Finds the index of a heredoc token in the heredoc arrays
 * @param mini Shell state
 * @param token Token to find
 * @return index in the arrays, or -1 if not found
 */
static int	find_heredoc_index(t_mini *mini, t_token *token)
{
	int	i;

	if (!mini || !token || !mini->heredoc_tokens)
		return (-1);
	i = 0;
	while (i < mini->heredoc_count)
	{
		if (mini->heredoc_tokens[i] == token)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Gets the file descriptor for a heredoc token
 * @param mini Shell state
 * @param token Heredoc token
 * @return File descriptor or -1 if not found
 */
static int	get_heredoc_fd(t_mini *mini, t_token *token)
{
	int	index;

	index = find_heredoc_index(mini, token);
	if (index == -1)
		return (-1);
	return (mini->heredoc_fds[index]);
}

/**
 * @brief Frees the heredoc arrays and closes file descriptors
 * @param mini Shell state
 */
void	free_heredoc_arrays(t_mini *mini)
{
	int	i;

	if (!mini)
		return ;
	if (mini->heredoc_fds)
	{
		i = 0;
		while (i < mini->heredoc_count)
		{
			if (mini->heredoc_fds[i] > 0)
				close(mini->heredoc_fds[i]);
			i++;
		}
		free(mini->heredoc_fds);
		mini->heredoc_fds = NULL;
	}
	if (mini->heredoc_tokens)
	{
		free(mini->heredoc_tokens);
		mini->heredoc_tokens = NULL;
	}
	mini->heredoc_count = 0;
}

/**
 * @brief Processes a single redir including heredoc
 * @param mini Shell state
 * @param token Redicrection token
 * @return 0 on success, 1 on failure
 */
int	process_single_redir_heredoc(t_mini *mini, t_token *token)
{
	int	fd;
	int	target_fd;

	if (token->type == HERE_DOC)
	{
		fd = get_heredoc_fd(mini, token);
		if (fd != -1)
		{
			target_fd = STDIN_FILENO;
			if (dup2(fd, target_fd) == -1)
				return (1);
			return (0);
		}
	}
	return (process_single_redir(token));
}

/**
 * @brief Modified version of apply_redir for preprocessed heredocs
 * @param mini Shell state
 * @param token Token list to process
 * @return 0 on success, 1 on failure
 */
int	apply_redir_heredoc(t_mini *mini, t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == CMD)
			break ;
		if (((current->type == RDIT && current->next->type == FILES)
			|| current->type == HERE_DOC) && current->next)
		{
			if (process_single_redir_heredoc(mini, current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}
