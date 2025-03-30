/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:20:31 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/30 03:49:57 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_current_directory(void)
{
	int		i;
	char	path[PATH_MAX + 1];

	i = 0;
	if (getcwd(path, PATH_MAX) == NULL)
		return (NULL);
	if (ft_strnstr(path, "home/", ft_strlen(path)))
	{
		while (path[i])
		{
			if (strncmp("home/", path + i, 5) == 0)
			{
				i += 5;
				while (path[i] && path[i] != '/')
					i++;
				if (!path[i])
					return (ft_strdup(" ~"));
				return (ft_strjoin(" ~", path + i));
			}
			i++;
		}
	}
	return (ft_strjoin(" ", path));
}

/**
 * @brief Gets USER from env
 * @param t_mini *mini
 */
static void	getuser(t_mini *mini)
{
	int		i;

	i = 0;
	if (mini->user)
		free(mini->user);
	if (!mini->envp)
	{
		mini->user = ft_strdup(COLOR_BLUE_ULTRA"user"COLOR_RESET);
		return ;
	}
	while (mini->envp[i])
	{
		if (ft_strnstr(mini->envp[i], "USER=", 5))
		{
			mini->user = ft_strjoin(COLOR_BLUE_ULTRA, mini->envp[i] + 5);
			return ;
		}
		i++;
	}
	mini->user = ft_strdup(COLOR_BLUE_ULTRA"user"COLOR_RESET);
}

char	*get_prompt(t_mini *mini)
{
	char	*prompt;
	char	*directory;
	char	*color;
	char	*temp;

	getuser(mini);
	if (mini->user == NULL)
	return (NULL);
	directory = NULL;
	directory = get_current_directory();
	if (!directory)
		return (show_err_msg("Myshell", "prompt fail"), NULL);
	color = ft_strjoin(COLOR_CYAN_ULTRA, directory);
	free(directory);
	if (!color)
		return (show_err_msg("Myshell", "prompt fail"), NULL);
	temp = ft_strjoin(mini->user, color);
	free(color);
	if (!temp)
		return (show_err_msg("Myshell", "prompt fail"), NULL);
	prompt = ft_strjoin(temp, COLOR_PURPLE_ULTRA" MyShell> "COLOR_RESET);
	free(temp);
	if (!prompt)
		return (show_err_msg("Myshell", "prompt fail"), NULL);
	return (prompt);
}
