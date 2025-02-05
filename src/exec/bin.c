/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:58 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/05 15:23:14 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_bin(t_mini *mini, char **cmd)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
		show_error("PID");
	if (pid == 0)
	{
		path = find_path(cmd[0], mini->envp);
		if (!path)
		{
			// free_cmd(cmd);
			show_error("Find path");
		}
		if (execve(path, cmd, mini->envp) == -1)
		{
			free(path);
			// free_cmd(cmd);
			show_error("Execve failed");
			return (1);
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
