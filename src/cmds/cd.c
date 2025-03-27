/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:34 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/27 17:38:38 by cbopp            ###   ########.fr       */
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

	new_var = ft_strjoin("OLDPWD=", old_dir);
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
 * @brief Handles path setup for cd command
 * @param mini shell state
 * @param cmd command arguments
 * @param current_dir current directory
 * @return path to change to or NULL on error
 */
static char	*setup_cd_path(t_mini *mini, char **cmd)
{
	char	*path;
	char	*expanded_path;
	int		ret;

	path = cmd[1];
	if (path && ft_strmincmp(path, "-", 1) == 0)
	{
		ret = change_to_oldpwd(&path, mini->envp);
		if (ret != 0)
			return (NULL);
		return (ft_strdup(path));
	}
	if (!path)
	{
		path = get_env_value(mini->envp, "HOME");
		if (!path)
		{
			show_err_return("cd", "HOME not set", ERR_GENERAL);
			return (NULL);
		}
		return (ft_strdup(path));
	}
	expanded_path = expand_tilde(path, mini->envp);
	return (expanded_path);
}

/**
 * @brief cd that updates PWD env and handles "-" and "~" options
 * @param mini Shell state
 * @param cmd Command arguements
 * @returns 0 on success, 1 on fail
 */
int	cd(t_mini *mini, char **cmd)
{
	char	current_dir[PATH_MAX];
	char	*path;

	if (cmd[1] && cmd[2])
		return (show_err_return("cd", "too many arguments", ERR_GENERAL));
	if (getcwd(current_dir, PATH_MAX) == NULL)
		return (show_err_return("cd", strerror(errno), ERR_GENERAL));
	path = setup_cd_path(mini, cmd);
	if (!path)
		return (ERR_GENERAL);
	if (access(path, F_OK) == -1)
		return (free(path), show_err_return("cd", ERR_NODIR, ERR_GENERAL));
	if (access(path, X_OK) == -1)
		return (free(path), show_err_return("cd", ERR_PERMISSION, ERR_GENERAL));
	if (chdir(path) == -1)
		return (free(path), show_err_return("cd", strerror(errno),
				ERR_GENERAL));
	free(path);
	return (update_pwd_vars(mini, current_dir));
}
