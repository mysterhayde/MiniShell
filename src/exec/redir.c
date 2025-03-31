/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:49:37 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/31 11:28:49 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Report an error message for file operations
 * @param filename Name of the file
 * @return None
 */
static void	report_file_error(char *filename)
{
	static int	already_reported = 0;

	if (already_reported)
		return ;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	already_reported = 1;
}

/**
 * @brief Opens a file for input redirection
 * @param filename name of the file to open
 * @return file descriptor or -1 on error
 */
int	open_file_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		report_file_error(filename);
	return (fd);
}

/**
 * @brief Opens a file for output redirection (truncate)
 * @param filename name of the file to open/create_pipes
 * @return file descriptor or -1 on error
 */
int	open_file_output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!access(filename, R_OK) && fd == -1)
		report_file_error(filename);
	return (fd);
}

/**
 * @brief Opens a file for output redirection (append)
 * @param filename name of the file to open/create
 * @return file descriptor or -1 on error
 */
int	open_file_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!access(filename, R_OK) && fd == -1)
		report_file_error(filename);
	return (fd);
}

/**
 * @brief Reset the error reporting flag, call this before each command
 * @return None
 */
void	reset_error_reporting(void)
{
	extern int	g_signo;
	int			temp;

	temp = g_signo;
	g_signo = 0;
	g_signo = temp;
}
