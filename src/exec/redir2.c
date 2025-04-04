/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:55:42 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/30 14:37:21 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Saves the original stdin/stdout file descriptors
 * @param saved_fd array to store the saved file descriptors
 */
void	save_std_fds(int saved_fd[2])
{
	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
}

/**
 * @brief Restores the original stdin/stdout file descriptors
 * @param saved_fd array containing the saved file descriptors
 */
void	restore_std_fds(int saved_fd[2])
{
	dup2(saved_fd[0], STDIN_FILENO);
	dup2(saved_fd[1], STDOUT_FILENO);
	close(saved_fd[0]);
	close(saved_fd[1]);
}

/**
 * @brief Process a single redirection
 * @param current redirection token
 * @return 0 on success, 1 on error
 */
int	process_single_redir(t_token *current)
{
	int	fd;

	if (ft_strmincmp(current->cmd[0], "<", 1) == 0)
		fd = open_file_input(current->next->cmd[0]);
	else if (ft_strmincmp(current->cmd[0], ">", 1) == 0)
		fd = open_file_output(current->next->cmd[0]);
	else if (ft_strmincmp(current->cmd[0], ">>", 2) == 0)
		fd = open_file_append(current->next->cmd[0]);
	else
		return (1);
	if (fd == -1)
		return (1);
	if (ft_strmincmp(current->cmd[0], "<", 1) == 0
		|| current->type == HERE_DOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

/**
 * @brief Applies the redirections in a token list
 * @param token pointer to the first token
 * @return 0 on success, 1 on error
 */
int	apply_redir(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if ((current->type == HERE_DOC || (current->type == RDIT
					&& current->next->type == FILES)) && current->next)
		{
			if (process_single_redir(current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}
