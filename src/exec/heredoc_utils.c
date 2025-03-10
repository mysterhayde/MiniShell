/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:22:18 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/10 19:07:15 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Generates a unique temporary filename
 * @param counter The counter to include in the filename
 * @return The generated filename or NULL on error
 */
char	*generate_temp_name(int counter)
{
	char	*base_path;
	char	*counter_str;
	char	*temp_name;

	base_path = "/tmp/minishell_heredoc_";
	counter_str = ft_itoa(counter);
	if (!counter_str)
		return (NULL);
	temp_name = ft_strjoin(base_path, counter_str);
	free(counter_str);
	return (temp_name);
}

/**
 * @brief Creates a temporary file for the here_doc
 * @param temp_name Pointer to store the filename
 * @return File descriptor for the temporary file, -1 on error
 */
int	create_temp_file(char **temp_name)
{
	int	fd;
	int	counter;

	counter = 0;
	*temp_name = NULL;
	while (counter < 1000)
	{
		*temp_name = generate_temp_name(counter);
		if (!(*temp_name))
			return (-1);
		fd = open(*temp_name, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd != -1)
			return(fd);
		free(*temp_name);
		counter++;
	}
	*temp_name = NULL;
	return (-1);
}

/**
 * @brief Checks if a line matches the delimiter exactly
 * @param line The input line
 * @param delimiter The delimiter to check against
 * @return 1 if matches, 0 if not
 */
static int	is_delimiter(char *line, char *delimiter)
{
	if (!line || !delimiter)
		return (0);
	if ((ft_strlen(line)) != ft_strlen(delimiter))
		return (0);
	return (ft_strmincmp(line, delimiter, ft_strlen(delimiter)) == 0);
}

/**
 * @brief Handles reading input for the here_doc in the child process
 * @param limiter The delimiter string to stop reading at
 * @param temp_fd File descriptor of the temporary file
 */
void	here_doc_child(char *limiter, int temp_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = readline("");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited ", 2);
			ft_putstr_fd("by end-of-file (wanted `", 2);
			ft_putstr_fd(limiter, 2);
			ft_putstr_fd("')\n", 2);
			break;
		}
		if (is_delimiter(line, limiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, temp_fd);
		ft_putstr_fd("\n", temp_fd);
		free(line);
	}
	close(temp_fd);
	exit(0);
}
