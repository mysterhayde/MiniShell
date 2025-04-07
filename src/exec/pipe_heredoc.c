/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:29:13 by cbopp             #+#    #+#             */
/*   Updated: 2025/04/07 10:46:26 by cbopp            ###   ########.fr       */
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
			perror("dup2 stdin");
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
 * @brief Prepares and executes the command within thepipe child process.
 * This includes variable/wildcard expansion and calling builtins or binaries.
 * @param mini Shell state
 * @param cmd_token The speecific comamnd token to execute.
 * @return Exit status of the command.
 */
static int	prepare_and_exec_cmd(t_mini *mini, t_token *cmd_token)
{
	int	ret;

	cmd_token->cmd = search_wildcard(cmd_token);
	if (!cmd_token->cmd)
		return (ERR_GENERAL);
	if (transform_string(cmd_token, mini->envp, mini->ret) != 0)
		return (ERR_GENERAL);
	fix_index(cmd_token);
	if (is_builtin(cmd_token->cmd[0]))
		ret = exec_builtin(mini, cmd_token->cmd);
	else
		ret = exec_bin(mini, cmd_token->cmd);
	return (ret);
}

/**
 * @brief Sets up pipe redirections for a command with heredoc support
 * @param mini Shell state
 * @param i Current command index
 * @param pipe_fds Array of pipe file descriptors
 */
void	handle_pipe_child_with_heredoc(t_mini *mini, int i, t_pipe *p)
{
	t_bool	is_last_cmd;
	t_token	*cmd_token;
	int		ret;

	is_last_cmd = (i == mini->pipe_num);
	setup_pipe_fds(mini, i, p->pipe_fds);
	close_pipe_fds(mini, p->pipe_fds);
	apply_pipe_redir_with_heredoc(mini, mini->token, is_last_cmd);
	cmd_token = skip_redirections(mini->token);
	if (cmd_token && cmd_token->cmd && cmd_token->cmd[0])
		ret = prepare_and_exec_cmd(mini, cmd_token);
	else
		ret = 0;
	free_pipe_resources(p);
	safe_exit(mini, ret);
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

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_pipe_child_with_heredoc(mini, i, p);
	}
	if (i > 0)
		close(p->pipe_fds[(i - 1) * 2]);
	if (i < mini->pipe_num)
		close(p->pipe_fds[i * 2 + 1]);
	return (pid);
}
