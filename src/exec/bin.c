/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:58 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 16:23:08 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	child_process(char *path, char **cmd, t_mini *mini)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(path, cmd, mini->envp) == -1)
	{
		free(path);
		show_error("Execve failed");
		exit(1);
	}
}

static int	handle_parent(char *path, pid_t pid)
{
	int	status;

	free(path);
	waitpid(pid, &status, 0);
	setup_signal_handlers();
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	return (WEXITSTATUS(status));
}

static int	execute_direct(char *path, char **cmd, t_mini *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free(path);
		show_error("PID");
		return (1);
	}
	if (pid == 0)
		child_process(path, cmd, mini);
	return (handle_parent(path, pid));
}

int	exec_bin(t_mini *mini, char **cmd)
{
	char	*path;

	path = find_path(cmd[0], mini->envp);
	if (!path)
	{
		show_error("Find path");
		return (1);
	}
	if (!mini->is_pipe)
		return (execute_direct(path, cmd, mini));
	child_process(path, cmd, mini);
	return (0);
}
