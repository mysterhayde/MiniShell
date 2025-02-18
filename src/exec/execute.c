/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:06 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 09:25:24 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Calls of expansion of argument(s) and then manages 
 * 		  builtin or bin commands
 * @param t_mini *mini
 * @details It checks for pipes anywhere in the input because if there's a pipe 
 * 			everything needs to be executed inside a fork. If there's no pipe 
 * 			builtin commands need to be executed without piping.
 */
void	execute(t_mini *mini)
{
	t_token	*tmp;

	tmp = mini->token;
	mini->is_pipe = FALSE;
	mini->pipe_num = 0;
	while (tmp && tmp->next)
	{
		if (tmp->type == PIPE)
		{
			mini->is_pipe = TRUE;
			mini->pipe_num++;
		}
		tmp = tmp->next;
	}
	if (mini->token->cmd && ft_strmincmp(mini->token->cmd[0], "exit", 4) == 0)
		exit_builtin(mini, mini->token->cmd);
	else if (mini->token->cmd && mini->is_pipe)
		mini->ret = minipipe(mini);
	else if (mini->token->cmd && is_builtin(mini->token->cmd[0])
		&& !mini->is_pipe)
		mini->ret = exec_builtin(mini, mini->token->cmd);
	else if (mini->token->cmd)
	{
		mini->ret = exec_bin(mini, mini->token->cmd);
	}
}
