/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:00:00 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/26 16:08:59 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Display EOF warning for heredoc
 * @param limiter The delimiter that was expected
 */
static void	display_heredoc_eof_warning(char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
}

/**
 * @brief Process a single line of heredoc input
 * @param line Input line
 * @param limiter Delimiter string
 * @param temp_fd File descriptor to write to
 * @return 1 if delimiter found, 0 to continue reading
 */
static int	process_heredoc_line(char *line, char *limiter, int temp_fd)
{
	if (is_delimiter(line, limiter))
	{
		free(line);
		return (1);
	}
	ft_putstr_fd(line, temp_fd);
	ft_putstr_fd("\n", temp_fd);
	free(line);
	return (0);
}

/**
 * @brief Reads lines for heredoc with custom prompt
 * @param limiter The delimiter to stop at
 * @param temp_fd File descriptor to write to
 * @param heredoc_num The heredoc number for the prompt
 */
static void	read_heredoc_lines(char *limiter, int temp_fd, int heredoc_num)
{
	char	*line;
	char	*prompt;

	prompt = create_heredoc_prompt(heredoc_num);
	if (!prompt)
		prompt = ft_strdup("heredoc> ");
	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			display_heredoc_eof_warning(limiter);
			break ;
		}
		if (process_heredoc_line(line, limiter, temp_fd))
			break ;
	}
	free(prompt);
}

/**
 * @brief Handles reading input for the here_doc in the child process
 * @param limiter The delimiter string to stop reading at
 * @param temp_fd File descriptor of the temporary file
 * @param heredoc_num The number of this heredoc
 */
void	here_doc_child_with_num(char *limiter, int temp_fd, int heredoc_num)
{
	//SIGNAL HANDLE
	
	read_heredoc_lines(limiter, temp_fd, heredoc_num);
	close(temp_fd);
	exit(0);
}
