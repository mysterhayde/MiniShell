/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:09:51 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/05 20:03:27 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief expand variables by searching in the env
 * @param str the variable you want expand
 * @param envp an array with environment variables
 * @details give a string containing only the variable to be expanded
 */
char	*expand(char *str, char **envp)
{
	int		i;
	int		j;
	int		len;
	char	*variable;
	char	*expanded;

	i = -1;
	j = 0;
	if (!envp)
		return (NULL);
	variable = ft_strjoin(str + 1, "=");
	if (!variable)
		return (NULL);
	len = ft_strlen(variable);
	while (envp[++i])
		if (ft_strmincmp(variable, envp[i], len) == 0)
			break ;
	if (!envp[i])
		return ("");
	expanded = malloc(sizeof(char) * (ft_strlen(envp[i]) - len + 1));
	if (!expanded)
		return (NULL);
	while (envp[i][len])
		expanded[j++] = envp[i][len++];
	expanded[j] = '\0';
	return (free(variable), expanded);
}
