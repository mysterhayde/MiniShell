/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:45:11 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/11 19:34:02 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Initialize readline history by loading from the file
 */
void	init_readline_history(t_mini *mini)
{
	load_history_from_file(mini);
}

/**
 * @brief Add a command to the history if its not empty
 * @param command The command to add
 */
void	add_to_history(t_mini *mini, const char *command)
{
	if (command && *command && command[0] != ' ')
	{
		add_history(command);
		save_history_to_file(mini, command);
	}
}

/**
 * @brief Process lines read from history file
 * @param lines Array of command lines
 */
void	process_history_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		if (lines[i][0] != '\0')
			add_history(lines[i]);
		i++;
	}
	ft_free_chartable(lines);
}

/**
 * @brief Clean up history before exit
 */
void	cleanup_history(void)
{
	rl_clear_history();
}

/**
 * @brief Get path to the history file in the home directory
 * @return Allocated string with the path, or NULL on failure
 */
char	*get_history_path(t_mini *mini)
{
	char	*home;
	char	*path;
	char	*result;

	home = get_env_value(mini->envp, "HOME");
	if (!home)
		return (ft_strdup(HISTORY_FILE));
	path = ft_strjoin(home, "/");
	if (!path)
		return (NULL);
	result = ft_strjoin(path, HISTORY_FILE);
	free(path);
	return (result);
}
