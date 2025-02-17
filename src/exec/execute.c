/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:06 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/11 12:47:26 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Launches all of the forks and manages the redirection of FDs
 * @param t_mini *mini
 */
int	minipipe(t_mini *mini)
{
	int		pipefd[2];
	int		i;

	i = 0;
	try_pipe(pipefd);
	while (i <= mini->pipe_num)
	{
		if (is_builtin(mini->token->cmd[0]))
		{
			mini->children->pid = fork();
			if (mini->children->pid == -1)
				perror("PID");
			if (mini->children->pid == 0)
				exec_builtin(mini, mini->token->cmd);
		}
		else
			exec_bin(mini, mini->token->cmd);
		i++;
	}

	while (i-- > 0)
		wait(NULL);
	return (0);
}

/**
 * @brief Calls of expansion of argument(s) and then manages builtin or bin commands
 * @param t_mini *mini
 * @details It checks for pipes anywhere in the input because if there's a pipe 
 * 			everything needs to be executed inside a fork. If there's no pipe 
 * 			builtin commands need to be executed without piping.
 */
void	execute(t_mini *mini)
{
	//Need to add ispipe check below
	if (mini->token->cmd && ft_strmincmp(mini->token->cmd[0], "exit", 4) == 0)
		exit_builtin(mini, mini->token->cmd);
	else if (mini->token->cmd && mini->is_pipe)
		mini->ret = minipipe(mini);
	else if (mini->token->cmd && is_builtin(mini->token->cmd[0]) && !mini->is_pipe)
		mini->ret = exec_builtin(mini, mini->token->cmd);
	else if (mini->token->cmd)
	{
		mini->ret = exec_bin(mini, mini->token->cmd);
	}
}
