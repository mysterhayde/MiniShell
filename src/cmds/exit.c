/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:41 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/21 08:41:34 by cbopp            ###   ########.fr       */
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

	if (!mini->is_pipe)
		ft_printf("exit\n");
	if (!cmd[1])
	{
		mini->exit = 1;
		return (0);
	}
	if (!is_numeric(cmd[1]))
	{
		show_err_msg("exit", ERR_NOTNUMERIC);
		mini->exit = 1;
		return (255);
	}
	if (cmd[2])
	{
		if (!mini->is_pipe)
			mini->exit = 0;
		return (show_err_return("exit", ERR_TOOMANY, ERR_BUILTIN));
	}
	status = ft_atoi(cmd[1]) & 255;
	mini->exit = 1;
	return (status);
}
