/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:45:11 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/25 13:29:47 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_history_file_path(void)
{
	char	*home;
	char	*path;

	home = getenv("HOME");
	if (!home)
		return (ft_strdup(HISTORY_FILE));
	path = ft_strjoin(home, "/");
	if (!path)
		return (NULL);
	home = ft_strjoin(path, HISTORY_FILE);
	free(path);
	return (home);
}

void	init_readline_history(void)
{
	rl_bind_key('\t', rl_complete);
	using_history();
	load_history_from_file();
}

void	add_to_history(const char *command)
{
	HIST_ENTRY	*last_entry;

	if (command && *command && command[0] != ' ')
	{
		last_entry = history_get(history_length);
		if (!last_entry || ft_strmincmp(last_entry->line, command,
				ft_strlen(command)) != 0)
			add_history(command);
	}
}

void	cleanup_history(void)
{
	save_history_to_file();
	clear_history();
	rl_clear_history();
}
