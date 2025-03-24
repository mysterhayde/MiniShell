/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:01:33 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/24 16:34:00 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Load history from file into readline
 */
void	load_history_from_file(t_mini *mini)
{
	char	*history_path;
	int		fd;
	char	buffer[PATH_MAX + 1];
	int		bytes_read;
	char	**lines;

	history_path = get_history_path(mini);
	if (!history_path)
		return ;
	fd = open(history_path, O_RDONLY);
	free(history_path);
	if (fd == -1)
		return ;
	bytes_read = read(fd, buffer, PATH_MAX);
	close(fd);
	if (bytes_read <= 0)
		return ;
	buffer[bytes_read] = '\0';
	lines = ft_split(buffer, '\n');
	if (!lines)
		return ;
	process_history_lines(lines);
}

static void	write_line_to_file(int fd, const char *line)
{
	char	*with_nl;

	with_nl = ft_strjoin(line, "\n");
	if (with_nl)
	{
		write(fd, with_nl, ft_strlen(with_nl));
		free(with_nl);
	}
}

void	save_history_to_file(t_mini *mini, const char *command)
{
	int		fd;
	char	*history_path;

	history_path = get_history_path(mini);
	fd = open(history_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	write_line_to_file(fd, command);
	free(history_path);
	close(fd);
}
