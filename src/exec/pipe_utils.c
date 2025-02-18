/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:50:34 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 17:24:02 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_pipes(int pipe_count, int **pipe_fds)
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

void	close_all_pipes(int pipe_count, int *pipe_fds)
{
	int	i;

	i = 0;
	while (i < (pipe_count * 2))
		close(pipe_fds[i++]);
}

int	run_pipe_commands(t_mini *mini, t_pipe *p)
{
	int	i;

	i = 0;
	while (i <= mini->pipe_num)
	{
		p->pids[i] = exec_pipe_cmd(mini, i, p->pipe_fds);
		if (p->pids[i] == -1)
		{
			close_all_pipes(mini->pipe_num, p->pipe_fds);
			free(p->pipe_fds);
			free(p->pids);
			return (1);
		}
		if (i < mini->pipe_num)
			find_cmd(mini);
		i++;
	}
	return (0);
}

int	wait_pipe_children(t_mini *mini, t_pipe *p)
{
	int	i;
	int	status;

	close_all_pipes(mini->pipe_num, p->pipe_fds);
	free(p->pipe_fds);
	i = 0;
	while (i <= mini->pipe_num)
	{
		waitpid(p->pids[i], &status, 0);
		if (WIFSIGNALED(status))
			mini->ret = 128 + WTERMSIG(status);
		i++;
	}
	free(p->pids);
	setup_signal_handlers();
	return (mini->ret);
}
