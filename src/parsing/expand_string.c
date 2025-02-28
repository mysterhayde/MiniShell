/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:55:09 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/28 12:45:31 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*isolate_variable(char *str, char **envp)
{
	int		i;
	char	*variable;
	char	*str_expanded;

	i = 0;
	if (!envp)
		return (NULL);
	while (str[i] && str[i] != '\"' && str[i] != '\'' && str[i] != ' ')
		i++;
	variable = malloc(sizeof(char) * (i + 1));
	if (!variable)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '\"' && str[i] != '\'' && str[i] != ' ')
		variable[i] = str[i];
	variable[i] = '\0';
	str_expanded = expand(variable, envp);
	if (!str)
		return(NULL);
	return (str_expanded);
}

static char	*add_expand_string(char *str, char *expanded, int j)
{
	char	*new_str;

	while (str[j] && str[j] != ' ' && str[j] != '\"' && str[j] != '\'')
		j++;
	new_str = ft_strjoin(expanded, str + j);
	if (!new_str)
		return (NULL);
	free(expanded);
	return (free(str), new_str);
}

char	*expand_string(char *str, char **envp)
{
	int 	i;
	int		j;
	char	*temp;
	char	*expanded;
	
	i = 0;
	j = 0;
	if (!envp)
		return (NULL);
	while (str[i] && str[i] != '$')
		i++;
	temp = malloc(sizeof(char) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (str[j] && str[j] != '$')
		temp[i++] = str[j++];
	temp[i] = '\0';
	expanded =ft_strjoin(temp, isolate_variable(str + j, envp));
	if (!expanded)
		return (NULL);
	free(temp);
	return (add_expand_string(str, expanded, j));
}
