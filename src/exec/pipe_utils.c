/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:50:34 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/31 11:47:55 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Create pipe file descriptors for a pipeline
 * @param pipe_count number of pipes needed
 * @param pipe_fds pointer to store the pipe file descriptors
 * @return 1 on success, 0 on failure
 */
int	create_pipes(int pipe_count, int **pipe_fds)
{
	int	i;

	*pipe_fds = malloc(sizeof(int) * (pipe_count * 2));
	if (!*pipe_fds)
		return (0);
	i = 0;
	while (i < pipe_count)
	{
		if (pipe((*pipe_fds) + (i * 2)) == -1)
		{
			free(*pipe_fds);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief Close all pipe file descriptors
 * @param pipe_count number of pipes
 * @param pipe_fds pipe file descriptors to close
 */
void	close_all_pipes(int pipe_count, int *pipe_fds)
{
	int	i;

	i = 0;
	while (i < (pipe_count * 2))
		close(pipe_fds[i++]);
}

/**
 * @brief Find the next Pipe token or process parentheses
 * @param mini shell state
 * @return 1 if next command found, 0 otherwise
 */
static int	advance_to_next_pipe_cmd(t_mini *mini)
{
	t_token	*current;

	current = mini->token;
	while (current && current->type != PIPE)
	{
		if (current->type == LEFT_PAREN)
		{
			current = find_matching_paren(current);
			if (!current)
				return (0);
		}
		else
			current = current->next;
	}
	if (!current)
		return (0);
	mini->token = current->next;
	return (1);
}

/**
 * @brief Execute all commands in a pipeline
 * @param mini shell state
 * @param p pipe state structure
 * @return 0 on success, 1 on failure
 */
int	run_pipe_commands(t_mini *mini, t_pipe *p)
{
	int	i;

	i = 0;
	while (i <= mini->pipe_num)
	{
		p->pids[i] = exec_pipe_cmd(mini, i, p->pipe_fds);
		if (p->pids[i] == -1)
		{
			close_all_pipes(mini->pipe_num, p->pipe_fds);
			free_pipe_resources(p);
			return (1);
		}
		if (i < mini->pipe_num)
			advance_to_next_pipe_cmd(mini);
		i++;
	}
	return (0);
}

/**
 * @brief Wait for all child processes in a pipeline and return final status
 * @param mini shell state
 * @param p pipe state containing pids
 * @return exit status of the last command in the pipeline
 */
int	wait_pipe_children(t_mini *mini, t_pipe *p)
{
	int	i;
	int	status;
	int	last_status;

	close_all_pipes(mini->pipe_num, p->pipe_fds);
	i = -1;
	last_status = 0;
	setup_signal_handlers_fork();
	while (++i <= mini->pipe_num)
	{
		waitpid(p->pids[i], &status, 0);
		if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
		{
			last_status = handle_fork_signal(status);
			break ;
		}
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}
	if (last_status == 0 && mini->ret != 0)
		last_status = mini->ret;
	mini->ret = last_status;
	free_pipe_resources(p);
	return (last_status);
}
