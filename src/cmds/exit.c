/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:41 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/11 12:46:07 by cbopp            ###   ########.fr       */
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
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(t_mini *mini, char **cmd)
{
	int	status;

	ft_printf("exit\n");
	if (!cmd[1])
		return (mini->exit = 1, 0);
	if (!is_numeric(cmd[1]))
	{
		ft_printf("exit: %s: numeric argument required\n", cmd[1]);
		return (mini->exit = 1, 255);
	}
	if (cmd[2])
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	status = ft_atoi(cmd[1]) & 255;
	mini->exit = 1;
	return (status);
}
