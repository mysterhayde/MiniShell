/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:34 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/25 12:43:29 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_value(char **env, const char *name)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (match_var_name(env[i], name))
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

static int	change_to_oldpwd(char **path, char **envp)
{
	char	*oldpwd;

	oldpwd = get_env_value(envp, "OLDPWD=");
	if (!oldpwd)
		return (show_err_return("cd", "OLDPWD not set", ERR_GENERAL));
	*path = oldpwd;
	ft_printf("%s\n", *path);
	return (0);
}

static int	update_pwd_vars(t_mini *mini, char *old_dir)
{
	char	current_dir[PATH_MAX];
	char	*new_var;

	new_var = ft_strjoin("OLDWPWD=", old_dir);
	if (!new_var)
		return (show_err_return("cd", ERR_MALLOC, ERR_GENERAL));
	mini->envp = update_env_var(mini->envp, "OLDPWD", new_var);
	free(new_var);
	if (!mini->envp)
		return (show_err_return("cd", strerror(errno), ERR_GENERAL));
	if (getcwd(current_dir, PATH_MAX) == NULL)
		return (show_err_return("cd", strerror(errno), ERR_GENERAL));
	if (!set(&new_var, ft_strjoin("PWD=", current_dir)))
		return (show_err_return("cd", ERR_MALLOC, ERR_GENERAL));
	mini->envp = update_env_var(mini->envp, "PWD", new_var);
	free(new_var);
	if (!mini->envp)
		return (show_err_return("cd", ERR_MALLOC, ERR_GENERAL));
	return (0);
}

/**
 * @brief cd that updates PWD env and "-" option
 * @param constchar *path
 * @returns 0 on success, 1 on fail
 * @warning DOES NOT WORK WITH ABSOLUTE PATH
 */
int	cd(t_mini *mini, char **cmd)
{
	char	current_dir[PATH_MAX];
	char	*path;
	int		ret;

	if (getcwd(current_dir, PATH_MAX) == NULL)
		return (show_err_return("cd", strerror(errno), ERR_GENERAL));
	path = cmd[1];
	if (path && ft_strmincmp(path, "-", 1) == 0)
	{
		ret = change_to_oldpwd(&path, mini->envp);
		if (ret != 0)
			return (ret);
	}
	if (!path)
		if (!set(path, get_env_value(mini->envp, "HOME")))
			return (show_err_return ("cd", "HOME not set", ERR_GENERAL));
	if (access(path, F_OK) == -1)
		return (show_err_return("cd", ERR_NODIR, ERR_GENERAL));
	if (access(path, X_OK) == -1)
		return (show_err_return("cd", ERR_PERMISSION, ERR_GENERAL));
	if (chdir(path) == -1)
		return (show_err_return("cd", strerror(errno), ERR_GENERAL));
	return (update_pwd_vars(mini, current_dir));
}
