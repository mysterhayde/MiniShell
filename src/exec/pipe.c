/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:12 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/26 12:14:10 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Finds the next pipe token from the current position
 * @param token starting token
 * @return next pipe token or NULL if none found
 */
static t_token	*find_next_pipe(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == PIPE)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * @brief Applies redirectiojns up to the next pipe
 * @param token starting token
 */
static void	apply_pipe_redir(t_token *token)
{
	t_token	*current;
	t_token	*next_pipe;

	current = token;
	next_pipe = find_next_pipe(token);
	while (current && current != next_pipe)
	{
		if (current->type == RDIT && current->next
			&& current->next->type == FILES)
			process_single_redir(current);
		current = current->next;
	}
}

/**
 * @brief Sets up pipe redirections and applies file redicrections for a command
 * @param i current command index
 * @param mini shell state
 * @param pipe_fds array of pipe file descriptors
 */
static void	handle_pipe_child(int i, t_mini *mini, int *pipe_fds)
{
	int		j;

	j = 0;
	if (i > 0)
	{
		dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO);
		close(pipe_fds[(i - 1) * 2]);
	}
	if (i < mini->pipe_num)
	{
		dup2(pipe_fds[i * 2 + 1], STDOUT_FILENO);
		close(pipe_fds[i * 2 + 1]);
	}
	while (j < (mini->pipe_num * 2))
		close(pipe_fds[j++]);
	apply_pipe_redir(mini->token);
}

/**
 * @brief Executes a command in a pipeline
 * @param mini shell state
 * @param i current command index
 * @param pipe_fds array of pipe file descriptors
 * @return process ID on success, -1 on failure
 */
int	exec_pipe_cmd(t_mini *mini, int i, int *pipe_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_pipe_child(i, mini, pipe_fds);
		if (is_builtin(mini->token->cmd[0]))
			exit(exec_builtin(mini, mini->token->cmd));
		else
			exec_bin(mini, mini->token->cmd);
		exit(1);
	}
	if (i > 0)
		close(pipe_fds[(i - 1) * 2]);
	if (i < mini->pipe_num)
		close(pipe_fds[i * 2 + 1]);
	return (pid);
}

/**
 * @brief Executes a pipeline of commands
 * @param mini shell state
 * @return exit status of the last command
 */
int	minipipe(t_mini *mini)
{
	t_pipe	p;

	if (ft_strmincmp(mini->token->cmd[0], "exit", 4) == 0)
		return (mini->exit = 1, exit_builtin(mini, mini->token->cmd));
	if (!create_pipes(mini->pipe_num, &p.pipe_fds))
		return (1);
	p.pids = malloc(sizeof(pid_t) * (mini->pipe_num + 1));
	if (!p.pids)
		return (free(p.pipe_fds), 1);
	if (run_pipe_commands(mini, &p, mini->token->cmd) == 1)
		return (1);
	return (wait_pipe_children(mini, &p));
}
