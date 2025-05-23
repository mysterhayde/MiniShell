/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:34:38 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/09 09:53:51 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_heredoc_signal(int signal)
{
	if (signal == SIGINT)
		g_signo = SIGINT;
	if (signal == SIGQUIT)
		g_signo = SIGQUIT;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
	close(STDIN_FILENO);
}

/**
 * @brief Waits for the here_doc child process to complete
 * @param pid Process ID of the child
 * @param temp_fd File descriptor of the temp file
 * @param temp_name Name of the temporary file
 * @return 0 on success, -1 on error
 */
static int	wait_here_doc(pid_t pid, int temp_fd, char *temp_name, t_mini *mini)
{
	int	status;
	int	read_fd;

	setup_signal_handlers_fork();
	close(temp_fd);
	waitpid(pid, &status, 0);
	if ((WIFEXITED(status) && WEXITSTATUS(status)) != 0
		|| (WIFSIGNALED(status) && WIFSIGNALED(status != 0)))
	{
		mini->ret = handle_fork_signal(status);
		unlink(temp_name);
		free(temp_name);
		return (setup_signal_handlers(mini), -1);
	}
	read_fd = open(temp_name, O_RDONLY);
	unlink(temp_name);
	free(temp_name);
	if (read_fd == -1)
		return (setup_signal_handlers(mini), -1);
	mini->ret = 0;
	return (setup_signal_handlers(mini), read_fd);
}

/**
 * @brief Implements here_doc functionality with numbered prompt
 * @param limiter The delimiter string to stop reading at
 * @param heredoc_num The number of this heredoc
 * @return File descriptor for reading, -1 on error
 */
int	here_doc_with_num(t_mini *mini, char *limiter, int heredoc_num)
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
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc_signal);
		signal(SIGQUIT, handle_heredoc_signal);
		free(temp_name);
		here_doc_child_with_num(mini, limiter, temp_fd, heredoc_num);
	}
	return (wait_here_doc(pid, temp_fd, temp_name, mini));
}
