/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:58 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/28 16:31:46 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	child_process(char *path, char **cmd, t_mini *mini)
{
	struct stat	path_stat;

	if (access(path, F_OK) == -1)
	{

	(void) mini;		free(path);
		show_error_exit(cmd[0], "No such file or directory", 127);
	}
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		free(path);
		show_error_exit(cmd[0], "Is a directory", 126);
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

static int	handle_parent(char *path, pid_t pid, t_mini *mini)
{
	int	status;

	setup_signal_handlers_fork();
	free(path);
	if (waitpid(pid, &status, 0) == -1)
		return (show_err_return("waitpid", "Wait failed", ERR_GENERAL));
	if (WIFSIGNALED(status))
		return (handle_fork_signal(status));
	setup_signal_handlers(mini);
	return (WEXITSTATUS(status));
}

static int	execute_direct(char *path, char **cmd, t_mini *mini)
{
	pid_t		pid;
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		show_err_msg(cmd[0], "Is a directory");
		free(path);
		return (126);
	}
	pid = fork();
	if (pid == -1)
	{
		free(path);
		return (show_err_return(cmd[0], "fork failed", 126));
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		child_process(path, cmd, mini);
	}
	return (handle_parent(path, pid, mini));
}

static int	handle_direct_path(t_mini *mini, char **cmd)
{
	char		*path;
	struct stat	path_stat;

	if (stat(cmd[0], &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (show_err_return(cmd[0], "Is a directory", 126));
		path = ft_strdup(cmd[0]);
		if (!path)
			return (127);
		if (!mini->is_pipe)
			return (execute_direct(path, cmd, mini));
		child_process(path, cmd, mini);
		free(path);
		return (0);
	}
	return (show_err_return(cmd[0], "No such file or directory", 127));
}

int	exec_bin(t_mini *mini, char **cmd)
{
	char	*path;
	int		ret;

	if (!cmd[0] || cmd[0][0] == '\0')
		return (0);
	if (cmd[0] && ft_strchr(cmd[0], '/') && mini->token->type == CMD)
	{
		ret = handle_direct_path(mini, cmd);
		if (ret >= 0)
			return (ret);
	}
	path = find_path(cmd[0], mini->envp);
	if (!path)
		return (show_cmd_not_found(cmd[0]), 127);
	if (!mini->is_pipe)
		return (execute_direct(path, cmd, mini));
	child_process(path, cmd, mini);
	free(path);
	return (0);
}
