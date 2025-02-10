/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:44 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/10 12:39:19 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_export_list(char	**envp)
{
	int		i;
	char	*eq;

	i = 0;
	while (envp && envp[i])
	{
		ft_printf("declare -x ");
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			write(1, envp[i], eq - envp[i] + 1);
			ft_printf("\"%s\"", eq + 1);
		}
		else
			ft_printf("%s", envp[i]);
		ft_printf("\n");
		i++;
	}
	return (0);
}

char	**add_env_var(char **envp, char *new_var)
{
	char	**new_env;
	int		i;
	int		len;

	len = 0;
	while (envp[len])
		len++;
	if (!set(&new_env, malloc(sizeof(char *) * (len + 2))))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (!set(&new_env[i], ft_strdup(envp[i])))
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	if (!set(&new_env[i], ft_strdup(new_var)))
		return (ft_free_chartable(new_env), NULL);
	new_env[i + 1] = NULL;
	return (new_env);
}

char	**update_env_var(char **envp, char *var_name, char *new_var)
{
	int		i;
	int		name_len;
	char	*new_str;

	name_len = 0;
	while (var_name[name_len] && var_name[name_len] != '=')
		name_len++;
	i = 0;
	while (envp[i])
	{
		if (ft_strmincmp(envp[i], var_name, name_len) == 0
			&& (envp[i][name_len] == '=' || !envp[i][name_len]))
		{
			if (!set(&new_str, ft_strdup(new_var)))
				return (NULL);
			free(envp[i]);
			envp[i] = new_str;
			return (envp);
		}
		i++;
	}
	ft_printf("Adding new var: %s\n", new_var);
	return (add_env_var(envp, new_var));
}

static int	handle_export_arg(char	***env_ptr, char *arg)
{
	char	**new_env;

	if (!is_valid_identifier(arg))
	{
		ft_printf("export: '%s': not a valid identifier\n", arg);
		return (0);
	}
	new_env = update_env_var(*env_ptr, arg, arg);
	if (!new_env)
		return (1);
	if (new_env != *env_ptr)
	{
		ft_free_chartable(*env_ptr);
		*env_ptr = new_env;
	}
	return (0);
}

int	export(t_mini *mini, char **cmd)
{
	char	**tempenv;
	int		i;

	if (!cmd[1])
		return (print_export_list(mini->envp));
	if (!(tempenv = copy_env(mini->envp)))
		return (1);
	i = 1;
	while (cmd[i])
	{
		if (handle_export_arg(&tempenv, cmd[i]) != 0)
			return (ft_free_chartable(tempenv), 1);
		i++;
	}
	ft_free_chartable(mini->envp);
	mini->envp = tempenv;
	return (0);
}
