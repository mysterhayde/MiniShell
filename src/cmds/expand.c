/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:09:51 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/09 15:03:18 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Helper function to extract the expanded value from env var
 * @param envp an array with env variables
 * @param i index of the found env var
 * @param len length of the variable name plus equals sign
 * @return allocated string with expanded value
 */
static char	*get_expanded_value(char **envp, int i, int len)
{
	char	*expanded;
	int		j;

	j = 0;
	expanded = malloc(sizeof(char) * (ft_strlen(envp[i]) - len + 1));
	if (!expanded)
		return (NULL);
	while (envp[i][len])
		expanded[j++] = envp[i][len++];
	expanded[j] = '\0';
	return (expanded);
}

/**
 * @brief expand variables by searching in the env
 * @param str the variable you want expand
 * @param envp an array with environment variables
 * @details give a string containing only the variable to be expanded
 */
char	*expand(char *str, char **envp)
{
	int		i;
	int		len;
	char	*variable;

	i = -1;
	if (!envp)
		return (NULL);
	variable = ft_strjoin(str + 1, "=");
	if (!variable)
		return (NULL);
	len = ft_strlen(variable);
	while (envp[++i])
		if (ft_strmincmp(variable, envp[i], len) == 0)
			break ;
	free(variable);
	if (!envp[i])
		return (ft_strdup(""));
	return (get_expanded_value(envp, i, len));
}
