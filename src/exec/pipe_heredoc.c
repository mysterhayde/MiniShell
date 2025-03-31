/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:29:13 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/31 11:46:29 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Sets up pipe input/output redirections
 * @param mini Shell state
 * @param i Current command index
 * @param pipe_fds Array of piep file descriptors
 */
static void	setup_pipe_fds(t_mini *mini, int i, int *pipe_fds)
{
	if (i > 0)
	{
		if (dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO) == -1)
		{
			perror("dup2");
			safe_exit(mini, 1);
		}
	}
	if (i < mini->pipe_num)
	{
		if (dup2(pipe_fds[i * 2 + 1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			safe_exit(mini, 1);
		}
	}
}

/**
 * @brief Closes all pipe file descriptors
 * @param mini Shell state with pipe number
 * @param pipe_fds Array of pipe file descriptors
 */
static void	close_pipe_fds(t_mini *mini, int *pipe_fds)
{
	int	j;

	j = 0;
	while (j < (mini->pipe_num * 2))
	{
		close(pipe_fds[j]);
		j++;
	}
}

/**
 * @brief Process redirections for a command based on position
 * @param mini Shell state
 * @param is_last_cmd Flag indicating
 */
static void	process_cmd_redirections(t_mini *mini, t_bool is_last_cmd)
{
	t_token	*current;
	t_token	*next_pipe;

	current = mini->token;
	next_pipe = find_next_pipe_token(mini->token);
	while (current && current != next_pipe)
	{
		if (((current->type == RDIT && current->next
					&& current->next->type == FILES)
				|| current->type == HERE_DOC) && current->next)
		{
			if (!should_skip_token(current, is_last_cmd))
				process_single_redir_with_heredoc(mini, current);
		}
		current = current->next;
	}
}

/**
 * @brief Sets up pipe redirections for a command with heredoc support
 * @param mini Shell state
 * @param i Current command index
 * @param pipe_fds Array of pipe file descriptors
 */
void	handle_pipe_child_with_heredoc(t_mini *mini, int i, int *pipe_fds)
{
	t_bool	is_last_cmd;

	is_last_cmd = (i == mini->pipe_num);
	setup_pipe_fds(mini, i, pipe_fds);
	close_pipe_fds(mini, pipe_fds);
	process_cmd_redirections(mini, is_last_cmd);
}

/**
 * @brief Executes a command in a pipeline with heredoc support
 * @param mini Shell state
 * @param i Current command index
 * @param pipe_fds Array of pipe file descriptors
 * @return Process ID or -1 on failure
 */
int	exec_pipe_cmd_with_heredoc(t_mini *mini, int i, t_pipe *p)
{
	pid_t	pid;
	t_token	*cmd_token;
	int		ret;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_pipe_child_with_heredoc(mini, i, p->pipe_fds);
		cmd_token = skip_redirections(mini->token);
		if (cmd_token && cmd_token->cmd && cmd_token->cmd[0])
			ret = check_string(mini, cmd_token);
		else
			ret = 0;
		free_pipe_resources(p);
		safe_exit(mini, ret);
	}
	if (i > 0)
		close(p->pipe_fds[(i - 1) * 2]);
	if (i < mini->pipe_num)
		close(p->pipe_fds[i * 2 + 1]);
	return (pid);
}
