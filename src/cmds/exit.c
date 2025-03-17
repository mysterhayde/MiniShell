/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:41 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/13 18:09:51 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || str[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(t_mini *mini, char **cmd)
{
	int	status;

	if (!mini->is_pipe)
		ft_printf("exit\n");
	if (!cmd[1])
	{
		mini->exit = 1;
		return (0);
	}
	if (!is_numeric(cmd[1]))
	{
		mini->exit = 1;
		mini->ret = 2;
		return (2);
	}
	if (cmd[2])
	{
		if (!mini->is_pipe)
			mini->exit = 0;
		show_error_exit("exit", ERR_TOOMANY, ERR_GENERAL);
	}
	status = ft_atoi(cmd[1]) & 255;
	mini->exit = ft_atoi(cmd[1]);
	mini->ret = ft_atoi(cmd[1]);
	return (status);
}
