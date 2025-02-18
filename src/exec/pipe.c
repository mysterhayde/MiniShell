/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:12 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 10:06:17 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_pipe_child(int i, int pipe_count, int *pipe_fds)
{
	int	j;
	int	fd_in;
	int	fd_out;

	j = 0;
	if (i > 0)
	{
		fd_in = pipe_fds[(i - 1) * 2];
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (i < pipe_count)
	{
		fd_out = pipe_fds[i * 2 + 1];
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	while (j < (pipe_count * 2))
	{
		close(pipe_fds[j]);
		j++;
	}
}

static void	close_pipes(int pipe_count, int *pipe_fds)
{
	int	i;

	i = 0;
	while (i < (pipe_count * 2))
	{
		close(pipe_fds[i]);
		i++;
	}
}

static int	create_pipes(int pipe_count, int **pipe_fds)
{
	int	i;

	*pipe_fds = malloc(sizeof(int) * (pipe_count * 2));
	if (!*pipe_fds)
		return (0);
	i = 0;
	while (i < pipe_count)
	{
		if (pipe((*pipe_fds) + (i * 2)) == -1)
		{
			free(*pipe_fds);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	handle_parent_pipes(int i, int pipe_count, int *pipe_fds)
{
	if (i > 0)
		close(pipe_fds[(i - 1) * 2]);     // Close read end of previous pipe
	if (i < pipe_count)
		close(pipe_fds[i * 2 + 1]);       // Close write end of current pipe
}

static int	execute_piped_command(t_mini *mini, int i, int *pipe_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		handle_pipe_child(i, mini->pipe_num, pipe_fds);
		if (is_builtin(mini->token->cmd[0]))
			exit(exec_builtin(mini, mini->token->cmd));
		else
			exec_bin(mini, mini->token->cmd);
	}
	handle_parent_pipes(i, mini->pipe_num, pipe_fds);
	return (pid);
}

int	minipipe(t_mini *mini)
{
	int		*pipe_fds;
	int		i;
	pid_t	*pids;

	if (!create_pipes(mini->pipe_num, &pipe_fds))
		return (1);
	pids = malloc(sizeof(pid_t) * (mini->pipe_num + 1));
	if (!pids)
		return (free(pipe_fds), 1);
	i = 0;
	while (i <= mini->pipe_num)
	{
		pids[i] = execute_piped_command(mini, i, pipe_fds);
		if (pids[i] == -1)
			return (close_pipes(mini->pipe_num, pipe_fds),
				free(pipe_fds), free(pids), 1);
		if (i < mini->pipe_num)
			find_cmd(mini);
		i++;
	}
	close_pipes(mini->pipe_num, pipe_fds);
	i = 0;
	while (i <= mini->pipe_num)
		waitpid(pids[i++], NULL, 0);
	return (free(pipe_fds), free(pids), 0);
}
