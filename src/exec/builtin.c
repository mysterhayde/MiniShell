/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:19 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/13 18:05:19 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Manages builtin command execution
 * @param t_mini *mini
 * @param char *cmd
 * @returns Result of command executed
 */
int	exec_builtin(t_mini *mini, char **cmd)
{
	int	ret;

	ret = 1;
	if (ft_strmincmp(cmd[0], "exit", 4) == 0)
		ret = exit_builtin(mini, mini->token->cmd);
	else if (ft_strmincmp(cmd[0], "pwd", 3) == 0)
		ret = pwd(mini);
	else if (ft_strmincmp(cmd[0], "export", 6) == 0)
		ret = export(mini, cmd);
	else if (ft_strmincmp(cmd[0], "cd", 2) == 0)
		ret = cd(mini, cmd);
	else if (ft_strmincmp(cmd[0], "env", 3) == 0)
		ret = env(mini);
	else if (ft_strmincmp(cmd[0], "echo", 4) == 0)
		ret = echo(cmd);
	else if (ft_strmincmp(cmd[0], "unset", 5) == 0)
		ret = unset(mini, cmd);
	return (ret);
}

/**
 * @brief Check if a command is a builtin or not
 * @param char *cmd
 * @returns 1 if builtin, 0 if /bin
 */
int	is_builtin(char *cmd)
{
	if (ft_strmincmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strmincmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strmincmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strmincmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strmincmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strmincmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strmincmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);
}
