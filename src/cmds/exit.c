/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:41 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/31 10:37:07 by hdougoud         ###   ########.fr       */
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

/**
 * @brief Process non-numeric exit argument
 * @param mini Shell state
 * @return Exit status (2)
 */
static int	handle_non_num_exit(t_mini *mini)
{
	mini->exit = 1;
	mini->ret = 2;
	show_err_msg("exit", "numeric argument required");
	return (2);
}

/**
 * @brief Exists the program for child processes
 * @param mini Shell state
 * @param status Exit status
 */
void	child_exit(t_mini *mini, int status)
{
	free_heredoc_arrays(mini);
	free_token_list(mini);
	free_all(mini);
	cleanup_history();
	exit(status);
}

/**
 * @brief Handles the exit builtin in pipe context
 * @param mini Shell state
 * @param cmd Command arguments
 * @return Exit status
 */
int	handle_exit_in_pipe(t_mini *mini, char **cmd)
{
	t_bool	is_exit;
	int		ret;

	is_exit = mini->exit;
	ret = exit_builtin(mini, cmd);
	mini->exit = is_exit;
	return (ret);
}

/**
 * @brief Built-in exit command implementation
 * @param mini Shell state
 * @param cmd Command arguments
 * @return Exit code or status
 */
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
		return (handle_non_num_exit(mini));
	if (cmd[2])
	{
		if (!mini->is_pipe)
			mini->exit = 0;
		show_error_exit("exit", ERR_TOOMANY, ERR_GENERAL);
	}
	status = ft_atoi(cmd[1]) & 255;
	mini->exit = ft_atoi(cmd[1]);
	mini->ret = ft_atoi(cmd[1]);
	if (mini->is_pipe)
		child_exit(mini, status);
	return (status);
}
