/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:55:09 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/03 23:00:11 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*isolate_variable(char *str, char **envp, int *len)
{
	int 	i;
	char	*variable;
	char	*expanded;

	i = 1;
	if (!envp)
		return (NULL);
	if (str[i] == '$')
		i++ ; 
	while (ft_isalnum(str[i]))
		i++;
	variable = ft_substr(str, 0, i);
	if (!variable)
		return (NULL);
	expanded = expand(variable, envp);
	if (!expanded)
		return(NULL);
	*(len) += i;
	return (free(variable), expanded);
}

char	*expand_string(char *str, char **envp)
{
	int 	i;
	char	*temp;
	char	*expanded;
	char	*new_str;
	
	i = 0;
	if (!envp)
		return (NULL);
	while (str[i] && str[i] != '$') 
		i++;
	temp = ft_substr(str, 0, i);
	if (!temp)
		return (NULL);
	expanded =ft_strjoin(temp, isolate_variable(str + i, envp, &i));
	if (!expanded)
		return (NULL);
	new_str = ft_strjoin(expanded, str + i);
	free(temp);
	free(expanded);
	return (free(str), new_str);
}
