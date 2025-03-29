/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:20:31 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/29 02:38:42 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_current_directory(char *current_dir)
{
	int		i;
	int		last_dir;
	char	path[PATH_MAX + 1];
	
	i = 0;
	if (getcwd(path, PATH_MAX) == NULL)
		return (NULL);
	while (path[i])
	{
		if (path[i] == '/')
			last_dir = i;
		i++;
	}
	i = 0;
	last_dir++;
	current_dir = malloc(sizeof(char) * ((ft_strlen(path)) + 2));
	if (!current_dir)
		return (NULL);
	current_dir[i++] = ' ';
	while (path[last_dir])
		current_dir[i++] = path[last_dir++];
	current_dir[i] = '\0';
	return (current_dir);
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
	directory = get_current_directory(directory);
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
	prompt = ft_strjoin(temp, COLOR_PURPLE_ULTRA" ~ MyShell> "COLOR_RESET);
	free(temp);
	if (!prompt)
		return (show_err_msg("Myshell", "prompt fail"), NULL);
	return (prompt);
}
