/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:06 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/26 11:54:19 by hdougoud         ###   ########.fr       */
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
	if (!mini->token->cmd)
		return ;
	if (ft_strmincmp(mini->token->cmd[0], "exit", 4) == 0)
		exit_builtin(mini, mini->token->cmd);
	else if (mini->is_pipe)
		mini->ret = minipipe(mini, mini->token->cmd);
	else if (is_builtin(mini->token->cmd[0]))
		mini->ret = exec_builtin(mini, mini->token->cmd);
	else
		mini->ret = exec_bin(mini, mini->token->cmd);
}
