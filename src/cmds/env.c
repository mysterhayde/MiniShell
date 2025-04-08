/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:39 by cbopp             #+#    #+#             */
/*   Updated: 2025/04/08 09:47:07 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	match_var_name(const char *env_var, const char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i] && var_name[i] != '=' && env_var[i]
		&& env_var[i] != '=' && env_var[i] == var_name[i])
		i++;
	return ((var_name[i] == '=' || !var_name[i])
		&& (env_var[i] == '=' || !env_var[i]));
}

char	**copy_env(char **env)
{
	char	**new_env;
	size_t	i;
	size_t	size;

	if (!env)
		return (NULL);
	size = get_env_size(env);
	if (!set(&new_env, (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (!set(&new_env[i], ft_strdup(env[i])))
		{
			free_env_arr(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

size_t	get_env_size(char **env)
{
	size_t	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

t_bool	is_valid_identifier(char *str)
{
	size_t	i;

	i = 0;
	if (!str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (FALSE);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * @brief prints all the environment variables
 * @returns 0 on success, 1 on fail
 */
int	env(t_mini *mini)
{
	if (!mini || !mini->envp)
		return (1);
	return (print_env(mini->envp));
}
