/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:58 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/26 17:35:58 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	child_process(char *path, char **cmd, t_mini *mini)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (access(path, F_OK) == -1)
	{
		free(path);
		show_error_exit(cmd[0], "No such file or directory", 127);
	}
	if (access(path, X_OK) == -1)
	{
		free(path);
		show_error_exit(cmd[0], "Permission denied", 126);
	}
	if (execve(path, cmd, mini->envp) == -1)
	{
		free(path);
		show_error_exit(cmd[0], strerror(errno), ERR_EXEC);
	}
}

static int	handle_parent(char *path, pid_t pid)
{
	int	status;

	free(path);
	if (waitpid(pid, &status, 0) == -1)
		return (show_err_return("waitpid", "Wait failed", ERR_GENERAL));
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
		return (show_err_return(cmd[0], "fork failed", 126));
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
		return (show_cmd_not_found(cmd[0]), 0);
	if (!mini->is_pipe)
		return (execute_direct(path, cmd, mini));
	child_process(path, cmd, mini);
	free(path);
	return (0);
}
