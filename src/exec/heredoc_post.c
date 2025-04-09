/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_post.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:00:00 by cbopp             #+#    #+#             */
/*   Updated: 2025/04/09 10:31:42 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Finds the index of a heredoc token in the heredoc arrays
 * @param mini Shell state
 * @param token Token to find
 * @return Index in the arrays, or -1 if not found
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
int	get_heredoc_fd(t_mini *mini, t_token *token)
{
	int	index;

	index = find_heredoc_index(mini, token);
	if (index == -1)
		return (-1);
	return (mini->heredoc_fds[index]);
}

/**
 * @brief Duplicates the heredoc file descriptor for use
 * @param mini Shell state
 * @param token Heredoc token
 * @return 0 on success, 1 on failure
 */
int	handle_heredoc_redirection(t_mini *mini, t_token *token)
{
	int	fd;
	int	target_fd;
	int	dup_fd;

	fd = get_heredoc_fd(mini, token);
	if (fd == -1)
		return (1);
	target_fd = STDIN_FILENO;
	dup_fd = dup(fd);
	if (dup_fd == -1)
		show_err_return("dup2", "failed", 1);
	if (dup2(fd, target_fd) == -1)
	{
		ft_putstr_fd("minishell: dup2 failed\n", 2);
		return (close(dup_fd), 1);
	}
	close(dup_fd);
	return (0);
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
			mini->heredoc_fds[i] = 0;
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
