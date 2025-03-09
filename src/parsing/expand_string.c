/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:55:09 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/09 15:13:33 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Replaces a variable in a string with its expanded value
 * @param str Original string containing the variable
 * @param expanded The expanded value of the variable
 * @param start Start index of the variable in the original string
 * @param end End index of the variable in the original string
 * @return New string with the variable replaced by its value
 */
static char	*replace_variable(char *str, char *expanded, int start, int end)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str) - (end - start) + ft_strlen(expanded);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start)
		result[j++] = str[i++];
	i = 0;
	while (expanded[i])
		result[j++] = expanded[i++];
	i = end;
	while (str[i])
		result[j++] = str[i++];
	result[j] = '\0';
	return (result);
}

/**
 * @brief Isolates a variable and returns its expanded value
 * @param str String containing a variable
 * @param i Index where the $ character is found
 * @param envp Environment variables list
 * @return Modified string with the expanded variable
 */
char	*isolate_variables(char *str, int i, char **envp)
{
	int		j;
	char	*var_name;
	char	*expanded;
	char	*result;

	j = i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, i, j - i);
	if (!var_name)
		return (str);
	expanded = expand(var_name, envp);
	free(var_name);
	if (!expanded)
		return (str);
	result = replace_variable(str, expanded, i, j);
	free(expanded);
	if (!result)
		return (str);
	free(str);
	return (result);
}

char	*expand_string(char *str, char **envp)
{
	int		i;
	char	*result;

	i = 0;
	if (!envp || !str)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$')
		{
			result = isolate_variables(result, i, envp);
			i = 0;
			continue;
		}
		i++;
	}
	free(str);
	return (result);
}
