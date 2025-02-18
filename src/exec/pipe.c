/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:12 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 17:21:01 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_pipe_child(int i, t_mini *mini, int *pipe_fds)
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
}

int	exec_pipe_cmd(t_mini *mini, int i, int *pipe_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_pipe_child(i, mini, pipe_fds);
		if (is_builtin(mini->token->cmd[0]))
			exit(exec_builtin(mini, mini->token->cmd));
		exec_bin(mini, mini->token->cmd);
		exit(1);
	}
	if (i > 0)
		close(pipe_fds[(i - 1) * 2]);
	if (i < mini->pipe_num)
		close(pipe_fds[i * 2 + 1]);
	return (pid);
}

int	minipipe(t_mini *mini)
{
	t_pipe	p;

	if (!create_pipes(mini->pipe_num, &p.pipe_fds))
		return (1);
	p.pids = malloc(sizeof(pid_t) * (mini->pipe_num + 1));
	if (!p.pids)
		return (free(p.pipe_fds), 1);
	if (run_pipe_commands(mini, &p) == 1)
		return (1);
	return (wait_pipe_children(mini, &p));
}
