/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:39:40 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/26 17:49:42 by hdougoud         ###   ########.fr       */
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
	if (apply_redir_with_heredoc(mini, token))
		return (restore_std_fds(saved_fd), 1);
	cmd_token = skip_redirections(token);
	if (!cmd_token)
		return (restore_std_fds(saved_fd), 0);
	if (is_builtin(cmd_token->cmd[0]))
		ret = exec_builtin(mini, cmd_token->cmd);
	else
		ret = exec_bin(mini, cmd_token->cmd);
	restore_std_fds(saved_fd);
	return (ret);
}

/**
 * @brief Initializes pipe structure with NULL pointers
 * @param p Pipe structure to initialize
 */
static int	prepare_pipe(t_mini *mini, t_pipe *p)
{
	p->pipe_fds = NULL;
	p->pids = NULL;
	if (!create_pipes(mini->pipe_num, &p->pipe_fds))
		return (1);
	p->pids = malloc(sizeof(pid_t) * (mini->pipe_num + 1));
	if (!p->pids)
	{
		free(p->pipe_fds);
		p->pipe_fds = NULL;
		return (1);
	}
	return (0);
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

	if (mini->token && mini->token->cmd
		&& ft_strmincmp(mini->token->cmd[0], "exit", 4) == 0)
		return (handle_exit_in_pipe(mini, mini->token->cmd));
	if (prepare_pipe(mini, &p))
		return (1);
	if (run_pipe_commands_with_heredoc(mini, &p) == 1)
		return (free_pipe_resources(&p), 1);
	ret = wait_pipe_children(mini, &p);
	return (ret);
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
		ret = check_string(mini, mini->token);
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
		return (check_string(mini, token));
	if (has_parentheses(token))
		ret = exec_paren_with_redir_heredoc(mini, token);
	else
		ret = check_string(mini, token);
	if (next_op->type == AND_OP)
		return (process_remaining_cmds_heredoc(mini, next_op->next, ret == 0));
	else if (next_op->type == OR_OP)
		return (process_remaining_cmds_heredoc(mini, next_op->next, ret != 0));
	return (ret);
}
