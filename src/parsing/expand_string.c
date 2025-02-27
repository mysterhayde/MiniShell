/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:55:09 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/27 17:00:41 by hdougoud         ###   ########.fr       */
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
		return (NULL); //print error
	i = -1;
	while (str[++i] && str[i] != '\"' && str[i] != '\'' && str[i] != ' ')
		variable[i] = str[i];
	variable[i] = '\0';
	str_expanded = expand(variable, envp);
	if (!str)
		return(NULL);
	return (str_expanded);
}

char	*expand_string(char *str, char **envp)
{
	int 	i;
	char	*temp;
	char	*expanded;
	
	i = 0;
	if (!envp)
		return (NULL);
	while (str[i] && str[i] != '$')
		i++;
	temp = malloc(sizeof(char) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (*str && *str != '$')
		temp[i++] = *str++;
	temp[i] = '\0';
	expanded =ft_strjoin(temp, isolate_variable(str, envp));
	if (!expanded)
		return (NULL);
	free(temp);
	while (*str && *str != ' ' && *str != '\"' && *str != '\'')
		str++;
	i = 0;
	temp = ft_strjoin(expanded, str);
	if (!temp)
		return (NULL);
	return (temp);
}
