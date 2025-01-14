/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:49:32 by hdougoud          #+#    #+#             */
/*   Updated: 2024/12/09 15:46:46 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*combine_line(char *line, char *buff)
{
	char	*joined_line;

	if (!buff)
		return (NULL);
	if (line == NULL)
	{
		joined_line = ft_strdup(buff);
		if (joined_line == NULL)
		{
			safe_free((void **) &line);
			return (NULL);
		}
	}
	else
	{
		joined_line = ft_strjoin(line, buff);
		if (joined_line == NULL)
		{
			safe_free((void **) &line);
			return (NULL);
		}
	}
	safe_free((void **) &line);
	return (joined_line);
}

static char	*read_line(int fd, char *current_line)
{
	int		bytes_read;
	char	buff[BUFFER_SIZE + 1];

	buff[0] = '\0';
	while (1)
	{
		if (ft_gnl_strchr(buff) == 1)
			break ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			safe_free((void **) &current_line);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buff[bytes_read] = '\0';
		current_line = combine_line(current_line, buff);
		if (current_line == NULL)
			return (NULL);
	}
	if (bytes_read == 0 && current_line == NULL)
		return (NULL);
	return (current_line);
}

static char	*manage_stash(char *line, char **stash)
{
	char	*backup;
	char	*complete_line;
	int		i;
	int		j;

	backup = line;
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (line);
	i++;
	backup += i;
	*stash = ft_strdup(backup);
	if (!*stash)
		return (free(line), NULL);
	complete_line = malloc(sizeof(char) * (i + 1));
	if (!complete_line)
		return (free(line), NULL);
	j = -1;
	while (++j < i)
		complete_line[j] = line[j];
	complete_line[j] = '\0';
	free(line);
	return (complete_line);
}

static char	*add_stash(char **stash, char *final_line)
{
	final_line = ft_strdup(*stash);
	safe_free((void **) stash);
	return (final_line);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAXFD];
	char		*final_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	final_line = NULL;
	if (stash[fd])
	{
		final_line = add_stash(&stash[fd], final_line);
		if (!final_line)
			return (NULL);
	}
	final_line = read_line(fd, final_line);
	if (final_line == NULL)
	{
		safe_free((void **) &stash[fd]);
		return (NULL);
	}
	final_line = manage_stash(final_line, &stash[fd]);
	if (final_line == NULL)
	{
		safe_free((void **) &stash[fd]);
		return (NULL);
	}
	return (final_line);
}

// #include <fcntl.h>

// int main(void)
// {
// 	int i = 0;
//     int fd = open("test.txt", O_RDONLY);
// 	char *line;

// 	if (fd == -1)
// 	{
// 		printf("Open failed\n");
// 		return (1);
// 	}    
// 	while (i < 15)
// 	{
// 		line = get_next_line(fd);
// 	    printf("Result %s\n", line);
// 		free(line);
// 		i++;
// 	}
// 	return (0);
// }