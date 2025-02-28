/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:40:34 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/28 16:01:45 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	transform_string(t_mini *mini, t_token *cmd_token)
{
	int	i;
	int	j;

	j = 0;
	while (cmd_token->cmd[j])
	{
		i = 0;
		while (cmd_token->cmd[j][i]) //USE string search
		{
			if (cmd_token->cmd[j][i] == '\'')
			{
				while(cmd_token->cmd[j][++i] && cmd_token->cmd[j][i] != '\'')
					;
				i++;
			}
			if (cmd_token->cmd[j][i++] == '$')
			{
				cmd_token->cmd[j] = expand_string(cmd_token->cmd[j], mini->envp);
				if (!cmd_token->cmd[j])
					exit(EXIT_FAILURE); //TODO : free all and return prompt
			}
		}
		i = 0;
		while (cmd_token->cmd[j][i])
		{
			if (cmd_token->cmd[j][i] == '\"' || cmd_token->cmd[j][i] == '\'')
			{
				cmd_token->cmd[j] = clean_quote(cmd_token->cmd[j]);
				if (!cmd_token->cmd[j])
					exit(EXIT_FAILURE); //TODO : free all and return prompt
			}
			i++;
		}
		j++;
	}
}

int	check_string(t_mini *mini, t_token *cmd_token)
{
	int	ret;

	transform_string(mini, cmd_token);
	if (is_builtin(cmd_token->cmd[0]))
		ret = exec_builtin(mini, cmd_token->cmd);
	else
		ret = exec_bin(mini, cmd_token->cmd);
	return (ret);
}
