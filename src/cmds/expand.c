/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:09:51 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/26 10:32:39 by hdougoud         ###   ########.fr       */
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

	i = 0;
	j = 0;
	variable = ft_strjoin(str + 1, "=");
	if (!variable)
		return (NULL);
	len = ft_strlen(variable);
	while (ft_strncmp(variable, envp[i], len))
		i++;
	if (!envp[i])
		return (NULL);
	expanded = malloc(sizeof(char) * (ft_strlen(envp[i]) - len + 1));
	if (!expanded)
		return (NULL);
	while (envp[i][len])
		expanded[j++] = envp[i][len++];
	expanded[j] = '\0';
	return (free(variable), expanded);
}
