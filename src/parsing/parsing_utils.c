/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:24:41 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/20 16:54:22 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	strlen_expanded(char **envp, const char *str, unsigned int *i)
{
	int		j;
	int		var;
	int		expanded;
	char	*var_str;

	j = 0;
	var = 0;
	expanded = 0;
	while (str[var] && str[var] != ' ' && str[var] != '\"')
		var++;
	var_str = malloc(sizeof(char) * var + 1);
	if (!var_str)
		return (0);
	while (j < var)
		var_str[j++] = str[(*i)++];
	var_str[j] = '=';
	j = 0;
	while (ft_strncmp(var_str, envp[j], var + 1))
		j++;
	while (envp[j][var++])
		expanded++;
	return (var);
}

size_t	ft_strlen_cleared(const char *str, char **envp)
{
	unsigned int	i;
	unsigned int	quotes;
	unsigned int	expanded;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
			quotes += 2;
			continue ;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				if (str[i] == '$')
					expanded = strlen_expanded(envp, str, &i);
				i++;
				continue ;
			}
			i++;
			quotes += 2;
		}
		i++;
	}
	return (i - quotes + expanded);
}

int	is_operator(t_mini *mini, char *str)
{
	if (ft_strmincmp(str, "|", 1) == 0)
	{
		mini->is_pipe = TRUE;
		mini->pipe_num++;
		return (PIPE);
	}
	else if (ft_strmincmp(str, "<", 1) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, ">", 1) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, ">>", 2) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, "<<", 2) == 0)
		return (HERE_DOC);
	return (0);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}
