/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:39:40 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/25 12:47:44 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Executes redirections with preprocessed heredocs
 * @param mini Shell state
 * @param token Token containing the command
 * @return Exit status
 */
int	exec_redirections_with_heredoc(t_mini *mini, t_token *token)
{
	int		saved_fd[2];
	int		ret;
	t_token	*cmd_token;

	save_std_fds(saved_fd);
	if (ft_strmincmp(token->cmd[0], "echo", 4) == 0
		&& token->cmd[1])
	{
		ret = check_string(mini, token);
		restore_std_fds(saved_fd);
		return (ret);
	}
	if (apply_redir_with_heredoc(mini, token))
		return (restore_std_fds(saved_fd), 1);
	cmd_token = skip_redirections(token);
	if (!cmd_token)
		return (restore_std_fds(saved_fd), 0);
	ret = check_string(mini, cmd_token);
	restore_std_fds(saved_fd);
	return (ret);
}

/**
 * @brief Executes a pipeline with preprocessed heredocs
 * @param mini Shell state
 * @return Exit status of the last command
 */
int	minipipe_with_heredoc(t_mini *mini)
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
		return (1);
	return (wait_pipe_children(mini, &p));
}

/**
 * @brief Executes a command with parenthesis and preprocessed heredocs
 * @param mini Shell state
 * @param token Token containing the command
 * @return Execution result
 */
int	exec_paren_with_redir_heredoc(t_mini *mini, t_token *token)
{
	t_token	*closing;
	t_token	*prev_token;
	int		ret;

	closing = find_matching_paren(token);
	if (!closing)
		return (1);
	prev_token = mini->token;
	mini->token = token->next;
	if (has_logical_ops(mini->token))
		ret = exec_logical_ops(mini, mini->token);
	else
		ret = exec_redirections_with_heredoc(mini, mini->token);
	mini->token = prev_token;
	return (ret);
}

/**
 * @brief Executes logical operations with redirections and preprocessed heredocs
 * @param mini Shell state
 * @param token Token list to process
 * @return Execution result
 */
int	exec_logical_with_redir_heredoc(t_mini *mini, t_token *token)
{
	t_token	*next_op;
	int		ret;

	if (!token)
		return (0);
	next_op = find_next_logical(token);
	if (!next_op)
		return (exec_redirections_with_heredoc(mini, token));
	if (has_parentheses(token))
		ret = exec_paren_with_redir_heredoc(mini, token);
	else
		ret = exec_redirections_with_heredoc(mini, token);
	if (next_op->type == AND_OP)
		return (process_remaining_cmds_heredoc(mini, next_op->next, ret == 0));
	else if (next_op->type == OR_OP)
		return (process_remaining_cmds_heredoc(mini, next_op->next, ret != 0));
	return (ret);
}
