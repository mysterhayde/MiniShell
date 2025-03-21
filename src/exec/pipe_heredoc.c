/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:37:51 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/21 14:14:39 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Finds the next pipe token
 * @param token Starting token
 * @return Next pipe token or NULL
 */
static t_token	*find_next_pipe_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == PIPE)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * @brief Applies redirections up to the next pipe with heredoc support
 * @param mini Shell state
 * @param token Starting token
 * @return 0 on success, 1 on failure
 */
int	apply_pipe_redir_heredoc(t_mini *mini, t_token *token)
{
	t_token	*current;
	t_token *next_pipe;

	current = token;
	next_pipe = find_next_pipe_token(token);
	while (current && current != next_pipe)
	{
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

/**
 * @brief Sets up pipe redirections for a command with heredoc support
 * @param mini Shell state
 * @param i Current command index
 * @param pipe_fds Array of pipe file descriptors
 */
void	handle_pipe_child_heredoc(t_mini *mini, int i, int *pipe_fds)
{
	int	j;

	j = 0;
	if (i > 0)
	{
		dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO);
		close(pipe_fds[(i - 1) * 2]);
	}
	if (i < mini->pipe_num)
	{
		dup2(pipe_fds[i * 2 + 1], STDOUT_FILENO);
		close(pipe_fds[i * 2 + 1]);
	}
	while (j < (mini->pipe_num * 2))
		close(pipe_fds[j++]);
	apply_pipe_redir_heredoc(mini, mini->token);
}

/**
 * @brief Executes a command in a pipeline with heredoc support
 * @param mini Shell state
 * @param i Current command index
 * @param pipe_fds Array of pipe file descriptors
 * @return Process ID or -1 on failure
 */
int	exec_pipe_cmd_heredoc(t_mini *mini, int i, int *pipe_fds)
{
	pid_t	pid;
	t_token	*cmd_token;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		//CHECK THIS
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_pipe_child_heredoc(mini, i, pipe_fds);
		cmd_token = skip_redirections(mini->token);
		if (cmd_token && cmd_token->cmd && cmd_token->cmd[0])
			check_string(mini, cmd_token);
		exit(mini->ret);
	}
	if (i > 0)
		close(pipe_fds[(i - 1) * 2]);
	if (i < mini->pipe_num)
		close(pipe_fds[i * 2 + 1]);
	return (pid);
}

/**
 * @brief Updates a pipeline of commands to use preprocessed heredocs
 * @param mini Shell state
 * @param p Pipe information structure
 * @return 0 on succcess, 1 on failure
 */
int	run_pipe_commands_heredoc(t_mini *mini, t_pipe *p)
{
	int		i;
	t_token	*current;

	i = 0;
	current = mini->token;
	while (i <= mini->pipe_num)
	{
		p->pids[i] = exec_pipe_cmd_heredoc(mini, i, p->pipe_fds);
		if (p->pids[i] == -1)
		{
			free(p->pipe_fds);
			free(p->pids);
			return (1);
		}
		if (i < mini->pipe_num)
		{
			current = find_next_pipe_token(current);
			if (current)
				current = current->next;
		}
		i++;
	}
	return (0);
}
