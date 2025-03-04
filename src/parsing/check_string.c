/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:40:34 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/04 18:33:53 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_var_error(char *cmd)
{
	ft_putstr_fd("minishell: error expanding variable in command: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

static char	*search_variable(char *str, char **envp, int *error)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i = 0;
		while (str[i])
		{
			if (str[i] == '\'')
			{
				while (str[++i] && str[i] != '\'')
					;
				i++;
			}
			if (str[i] == '$' && ft_isalnum(str[i + 1]))
			{
				str = expand_string(str, envp);
				if (!str)
					return(*error = 1, NULL);
				i = -1;
			}
			i++;
		}
	}
	return (str);
}

static int	transform_string(t_token *current, char **envp)
{
	int	j;
	int	error;

	j = 0;
	error = 0;
	while (current->cmd[j])
	{
		current->cmd[j] = search_variable(current->cmd[j], envp, &error);
		if (error || !current->cmd[j])
			return (handle_var_error(current->cmd[0]));
		if (strchr(current->cmd[j], '\"') || strchr(current->cmd[j], '\''))
		{
			current->cmd[j] = clean_quote(current->cmd[j]);
			if (!current->cmd[j])
				return (handle_var_error(current->cmd[0]));
		}
		j++;
	}
	return (0);
}

int	check_string(t_mini *mini, t_token *cmd_token)
{
	int	ret;

	if (transform_string(cmd_token, mini->envp) != 0)
		return (ERR_GENERAL);
	if (is_builtin(cmd_token->cmd[0]))
		ret = exec_builtin(mini, cmd_token->cmd);
	else
		ret = exec_bin(mini, cmd_token->cmd);
	mini->ret = ret;
	return (ret);
}
