/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:11:20 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/09 18:17:36 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Expands tilde (~) in a path
 * @param path Path potentially containing a tilde
 * @param envp Environment variables
 * @return Expanded path (must be freed) or NULL on error
 */
char	*expand_tilde(char *path, char **envp)
{
	char	*home;
	char	*expanded_path;
	int		i;

	if (!path || path[0] != '~')
		return (ft_strdup(path));
	if (path[1] == '/' || path[1] == '\0')
	{
		home = get_env_value(envp, "HOME");
		if (!home)
			return (ft_strdup(path));
		return (ft_strjoin(home, path + 1));
	}
	i = 1;
	while (path[i] && path[i] != '/')
		i++;
	home = get_env_value(envp, "HOME");
	if (home)
		expanded_path = ft_strjoin(home, path + i);
	else
		expanded_path = ft_strdup(path);
	return (expanded_path);
}

/**
 * @brief Frees an array of environment variables
 * @param env The environement array to free
 */
void	free_env_arr(char **env)
{
	size_t	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
