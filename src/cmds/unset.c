/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:39:58 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/21 08:01:17 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**remove_env_var(char **envp, int rm_index)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	if (!set(&new_env, malloc(sizeof(char *) * i)))
		return (NULL);
	i = -1;
	j = 0;
	while (envp[++i])
	{
		if (i != rm_index)
		{
			if (!set(&new_env[j++], ft_strdup(envp[i])))
			{
				new_env[j] = NULL;
				ft_free_chartable(new_env);
				return (NULL);
			}
		}
	}
	new_env[j] = NULL;
	return (new_env);
}

static int	handle_unset_arg(t_mini *mini, char *arg)
{
	int		i;
	char	**new_env;

	if (!is_valid_identifier(arg))
		return (show_err_return("unset", ERR_NOVALID, ERR_BUILTIN));
	i = 0;
	while (mini->envp[i])
	{
		if (match_var_name(mini->envp[i], arg))
		{
			new_env = remove_env_var(mini->envp, i);
			if (!new_env)
				return (show_err_return("unset", ERR_MALLOC, ERR_GENERAL));
			ft_free_chartable(mini->envp);
			mini->envp = new_env;
			break ;
		}
		i++;
	}
	return (0);
}

int	unset(t_mini *mini, char **cmd)
{
	int		i;
	int		ret;

	i = 1;
	while (cmd[i])
	{
		ret = handle_unset_arg(mini, cmd[i]);
		if (ret != 0)
			return (1);
		i++;
	}
	return (0);
}
