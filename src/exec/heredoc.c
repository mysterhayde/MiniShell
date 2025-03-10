/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:34:38 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/10 19:09:41 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Waits for the here_doc child process to complete
 * @param pid Process ID of the child
 * @param temp_fd File descriptor of the temp file
 * @param temp_name Name of the temporary file
 * @return 0 on success, -1 on error
 */
static int	wait_here_doc(pid_t pid, int temp_fd, char *temp_name)
{
	int	status;
	int	read_fd;

	close(temp_fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink(temp_name);
		free(temp_name);
		return (-1);
	}
	read_fd = open(temp_name, O_RDONLY);
	unlink(temp_name);
	free(temp_name);
	if (read_fd == -1)
		return (-1);
	return (read_fd);
}

/**
 * @brief Implements here_doc functionality using a temporary file
 * @param limiter The delimiter string to stop reading at
 * @return File descriptor for reading, -1 on error
 */
int	here_doc(char *limiter)
{
	pid_t	pid;
	int		temp_fd;
	char	*temp_name;

	temp_fd = create_temp_file(&temp_name);
	if (temp_fd == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(temp_fd);
		unlink(temp_name);
		free(temp_name);
		return(-1);
	}
	if (pid == 0)
		here_doc_child(limiter, temp_fd);
	return (wait_here_doc(pid, temp_fd, temp_name));
}
