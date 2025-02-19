/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayden <hayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:06 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/19 20:01:28 by hayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *expand(char *str)
{
	str = NULL;
	(void)str;
	return ("Variable expanded");
}

static void	check_expand(char **cmd)
{
	int	i;
	int	j;

	j = 0;
	while (cmd[j])
	{
		i = 0;
		while (cmd[j][i])
		{
			if (cmd[j][i] == '\'')
				break ;
			if (cmd[j][i] == '$')
				cmd[j] = expand(cmd[j]);
			i++;
		}
		j++;
	}
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
	if (!mini->token->cmd)
		return ;
	check_expand(mini->token->cmd);
	if (ft_strmincmp(mini->token->cmd[0], "exit", 4) == 0)
		exit_builtin(mini, mini->token->cmd);
	else if (mini->is_pipe)
		mini->ret = minipipe(mini);
	else if (is_builtin(mini->token->cmd[0]))
		mini->ret = exec_builtin(mini, mini->token->cmd);
	else
		mini->ret = exec_bin(mini, mini->token->cmd);
}
