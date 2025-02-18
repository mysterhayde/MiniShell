/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:58 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 10:01:38 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_bin(t_mini *mini, char **cmd)
{
	char	*path;
	pid_t	pid;

	path = find_path(cmd[0], mini->envp);
	if (!path)
	{
		show_error("Find path");
		exit(1);
	}
	if (!mini->is_pipe)
	{
		pid = fork();
		if (pid == -1)
			show_error("PID");
		if (pid == 0)
		{
			if (execve(path, cmd, mini->envp) == -1)
			{
				free(path);
				show_error("Execve failed");
				exit(1);
			}
		}
		else
		{
			free(path);
			waitpid(pid, NULL, 0);
			return (0);
		}
	}
	if (execve(path, cmd, mini->envp) == -1)
	{
		free(path);
		show_error("Execve failed");
		exit(1);
	}
	free(path);
	return (0);
}
