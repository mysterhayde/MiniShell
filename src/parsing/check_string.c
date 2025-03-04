/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:40:34 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/04 14:26:19 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*search_variable(char *str, char **envp)
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
					exit(EXIT_FAILURE); //TODO : free all and return prompt
				i = -1;
			}
			i++;
		}
	}
	return (str);
}

void	transform_string(t_token *current, char **envp)
{
	int	j;

	j = 0;
	while (current->cmd[j])
	{
		current->cmd[j] = search_variable(current->cmd[j], envp);
		if (strchr(current->cmd[j], '\"') || strchr(current->cmd[j], '\''))
		{
			current->cmd[j] = clean_quote(current->cmd[j]);
			if (!current->cmd[j])
				exit(EXIT_FAILURE); //TODO : free all and return prompt
		}
		j++;
	}
}

int	check_string(t_mini *mini, t_token *cmd_token)
{
	int	ret;

	transform_string(cmd_token, mini->envp);
	if (is_builtin(cmd_token->cmd[0]))
		ret = exec_builtin(mini, cmd_token->cmd);
	else
		ret = exec_bin(mini, cmd_token->cmd);
	return (ret);
}
