/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:28:04 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/24 13:36:22 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Handles redirection for input files
 * @param filename Name of input file
 * @return 0 on success, 1 on failure
 */
static int	handle_input_redir(char *filename)
{
	int	fd;
	int	target_fd;

	fd = open_file_input(filename);
	target_fd = STDIN_FILENO;
	if (fd == -1)
		return (1);
	if (dup2(fd, target_fd) == -1)
		return (close(fd), 1);
	close(fd);
	return (0);
}

/**
 * @brief Handles redirection for output files
 * @param filename Name of output file
 * @param append Flag for append mode
 * @return 0 on success, 1 on failure
 */
static int	handle_output_redir(char *filename, t_bool append)
{
	int	fd;
	int	target_fd;

	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open_file_output(filename);
	target_fd = STDOUT_FILENO;
	if (fd == -1)
		return (1);
	if (dup2(fd, target_fd) == -1)
		return (close(fd), 1);
	close(fd);
	return (0);
}

/**
 * @brief Processes a single redirection including heredoc
 * @param mini Shell state
 * @param token Redirection token
 * @return 0 on success, 1 on failure
 */
int	process_single_redir_with_heredoc(t_mini *mini, t_token *token)
{
	if (token->type == HERE_DOC)
		return (handle_heredoc_redirection(mini, token));
	else if (token->type == RDIT)
	{
		if (ft_strmincmp(token->cmd[0], "<", 1) == 0)
			return (handle_input_redir(token->next->cmd[0]));
		else if (ft_strmincmp(token->cmd[0], ">", 1) == 0)
			return (handle_output_redir(token->next->cmd[0], FALSE));
		else if (ft_strmincmp(token->cmd[0], ">>", 2) == 0)
			return (handle_output_redir(token->next->cmd[0], TRUE));
		return (1);
	}
	return (0);
}

/**
 * @brief Modified version of apply_redir for preprocessed heredocs
 * @param mini Shell state
 * @param token Token list to process
 * @return 0 on success, 1 on failure
 */
int	apply_redir_with_heredoc(t_mini *mini, t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == CMD)
			break ;
		if (((current->type == RDIT && current->next
					&& current->next->type == FILES)
				|| current->type == HERE_DOC) && current->next)
		{
			if (process_single_redir_with_heredoc(mini, current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}
