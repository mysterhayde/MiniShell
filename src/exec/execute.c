/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:06 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/26 12:14:00 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Check if the token list contains logical ops
 * @param token token list to check
 * @return true if logical ops are present, false otherwise
 */
t_bool	has_logical_ops(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == AND_OP || current->type == OR_OP)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

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
	if (!mini->token || !mini->token->cmd)
		return ;
	if (ft_strmincmp(mini->token->cmd[0], "exit", 4) == 0)
		mini->ret = exit_builtin(mini, mini->token->cmd);
	else if (has_logical_ops(mini->token))
		mini->ret = exec_logical_ops(mini, mini->token);
	else if (mini->is_pipe)
		mini->ret = minipipe(mini, mini->token->cmd);
	else
		mini->ret = exec_redirections(mini, mini->token);
}
