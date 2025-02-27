/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:01:33 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/25 13:20:00 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	process_history_lines(char **lines)
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

void	load_history_from_file(void)
{
	char	*history_path;
	int		fd;
	char	buffer[PATH_MAX + 1];
	int		bytes_read;

	history_path = get_history_file_path();
	if (!history_path)
		return ;
	fd = open(history_path, O_RDONLY);
	free(history_path);
	if (fd == -1)
		return ;
	bytes_read = read(fd, buffer, 4096);
	if (bytes_read <= 0)
	{
		close(fd);
		return ;
	}
	buffer[bytes_read] = '\0';
	close(fd);
	process_history_lines(ft_split(buffer, '\n'));
}

static void	write_history_entries(int fd, HIST_ENTRY **hist_list)
{
	int		i;
	char	*with_newline;

	if (!hist_list)
		return ;
	i = 0;
	while (hist_list[i])
	{
		with_newline = ft_strjoin(hist_list[i]->line, "\n");
		if (with_newline)
		{
			write(fd, with_newline, ft_strlen(with_newline));
			free(with_newline);
		}
		i++;
	}
}

void	save_history_to_file(void)
{
	char		*history_path;
	int			fd;
	HIST_ENTRY	**hist_list;

	history_path = get_history_file_path();
	if (!history_path)
		return ;
	fd = open(history_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(history_path);
	if (fd == -1)
		return ;
	hist_list = history_list();
	write_history_entries(fd, hist_list);
	close(fd);
}
