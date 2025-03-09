/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:40:34 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/09 15:30:25 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_error_code(char *str, int return_code)
{
	char *error_code;
	char *new_str;

	error_code = ft_itoa(return_code);
	if (!error_code)
		return (NULL);
	new_str = ft_strjoin(error_code, str + 2);
	if (!new_str)
		return (NULL);
	return (free(error_code), new_str);
}

static char	*search_error_code(int return_code, char *str)
{
	int		i;
	char	*temp;
	char	*new_str;
	char	*expanded;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += (skip_until_next_quote(str, str[i], i) - 1);
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			expanded = expand_error_code(str + i, return_code);
			temp = ft_substr(str, 0, i);
			new_str = ft_strjoin(temp, expanded);
			free(temp);
			free(expanded);
			if (!new_str)
				exit(EXIT_FAILURE); //TODO : free all and return prompt
			return (free(str), search_error_code(return_code, new_str));
		}
		i++;
	}
	return (str);
}

static char	*search_variable(char *str, char **envp)
{
	int		i;
	char	*temp;
	char	*new_str;
	char	*expanded;

	i = 0;
	while (str[i])
	{
			if (str[i] == '\'')
				i += (skip_until_next_quote(str, str[i], i) - 1);
			else if (str[i] == '$' && ft_isalnum(str[i + 1]))//check echo '$USER''$USER' AND check echo '$USER' $USER
			{
				printf("INSIDE EXPAND\n");
				expanded = expand_string(str + i, envp);
				temp = ft_substr(str, 0, i);
				new_str = ft_strjoin(temp, expanded);
				free(temp);
				free(expanded);
				if (!new_str)
					exit(EXIT_FAILURE); //TODO : free all and return prompt
				return (free(str), search_variable(new_str, envp));
			}
			i++;
	}
	return (str);
}

void	transform_string(t_token *current, char **envp, int return_code)
{
	int	j;

	j = 0;
	while (current->cmd[j])
	{
		current->cmd[j] = search_variable(current->cmd[j], envp);
		current->cmd[j] = search_error_code(return_code, current->cmd[j]);
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

	transform_string(cmd_token, mini->envp, mini->ret);
	if (is_builtin(cmd_token->cmd[0]))
		ret = exec_builtin(mini, cmd_token->cmd);
	else
		ret = exec_bin(mini, cmd_token->cmd);
	return (ret);
}
