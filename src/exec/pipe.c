/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:12 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/28 16:48:48 by hdougoud         ###   ########.fr       */
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
 * @brief Applies redirections up to the next pipe
 * @param token starting token
 * @return 0 on success, 1 on error
 */
static int	apply_pipe_redir(t_token *token)
{
	t_token	*current;
	t_token	*next_pipe;

	current = token;
	next_pipe = find_next_pipe(token);
	while (current && current != next_pipe)
	{
		if (((current->type == RDIT && current->next->type == FILES)
				|| current->type == HERE_DOC) && current->next)
		{
			if (process_single_redir(current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

/**
 * @brief Sets up pipe redirections and applies file redicrections for a command
 * @param i current command index
 * @param mini shell state
 * @param pipe_fds array of pipe file descriptors
 */
static void	handle_pipe_child(int i, t_mini *mini, int *pipe_fds)
{
	int	j;

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
	t_token	*cmd_token;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_pipe_child(i, mini, pipe_fds);
		cmd_token = skip_redirections(mini->token);
		if (cmd_token && cmd_token->cmd && cmd_token->cmd[0])
			check_string(mini, cmd_token);
		exit(mini->ret);
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
	int		ret;
	t_bool	is_exit;

	if (mini->token && mini->token->cmd
		&& ft_strmincmp(mini->token->cmd[0], "exit", 4) == 0)
	{
		is_exit = mini->exit;
		ret = exit_builtin(mini, mini->token->cmd);
		mini->exit = is_exit;
		return (ret);
	}
	if (!create_pipes(mini->pipe_num, &p.pipe_fds))
		return (1);
	p.pids = malloc(sizeof(pid_t) * (mini->pipe_num + 1));
	if (!p.pids)
		return (free(p.pipe_fds), 1);
	if (run_pipe_commands_with_heredoc(mini, &p) == 1)
		return (free_pipe_resources(&p), 1);
	return (wait_pipe_children(mini, &p));
}
