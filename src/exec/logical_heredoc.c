/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:20:00 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/25 13:27:57 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Saves heredoc state for later restoration
 * @param mini Shell state
 * @param heredoc_state Structure to save state to
 */
static void	save_heredoc_state(t_mini *mini, t_mini *heredoc_state)
{
	int	i;

	heredoc_state->heredoc_count = mini->heredoc_count;
	heredoc_state->isheredoc = mini->isheredoc;
	if (mini->heredoc_count > 0)
	{
		heredoc_state->heredoc_tokens = malloc(sizeof(t_token *)
				* mini->heredoc_count);
		heredoc_state->heredoc_fds = malloc(sizeof(int) * mini->heredoc_count);
		if (!heredoc_state->heredoc_tokens || !heredoc_state->heredoc_fds)
			return ;
		i = 0;
		while (i < mini->heredoc_count)
		{
			heredoc_state->heredoc_tokens[i] = mini->heredoc_tokens[i];
			heredoc_state->heredoc_fds[i] = mini->heredoc_fds[i];
			i++;
		}
	}
	else
	{
		heredoc_state->heredoc_tokens = NULL;
		heredoc_state->heredoc_fds = NULL;
	}
}

/**
 * @brief Restores heredoc state after command execution
 * @param mini Shell state
 * @param heredoc_state Structure containing saved state
 */
static void	restore_heredoc_state(t_mini *mini, t_mini *heredoc_state)
{
	int	i;

	if (mini->heredoc_tokens)
		free(mini->heredoc_tokens);
	if (mini->heredoc_fds)
	{
		i = 0;
		while (i < mini->heredoc_count)
		{
			if (mini->heredoc_fds[i] > 0)
				close(mini->heredoc_fds[i]);
			i++;
		}
		free(mini->heredoc_fds);
	}
	mini->heredoc_count = heredoc_state->heredoc_count;
	mini->isheredoc = heredoc_state->isheredoc;
	mini->heredoc_tokens = heredoc_state->heredoc_tokens;
	mini->heredoc_fds = heredoc_state->heredoc_fds;
}

/**
 * @brief Process remaining commands after logical operator with heredoc support
 * @param mini Shell state
 * @param tokens Tokens to process
 * @param condition Whether to execute (TRUE) or skip (FALSE)
 * @return Execution result
 */
int	process_remaining_cmds_heredoc(t_mini *mini, t_token *tokens,
	t_bool condition)
{
	t_state	state;
	t_mini	heredoc_state;
	int		ret;

	if (!tokens || !condition)
		return (mini->ret);
	save_exec_state(mini, &state);
	save_heredoc_state(mini, &heredoc_state);
	mini->token = tokens;
	if (is_parenthesis_cmd(tokens))
		ret = exec_parenthesis(mini);
	else if (has_logical_ops(tokens))
		ret = exec_logical_ops_heredoc(mini, tokens);
	else
		ret = check_string(mini, tokens);
	restore_heredoc_state(mini, &heredoc_state);
	restore_exec_state(mini, &state);
	return (ret);
}

/**
 * @brief Executes logical operations with heredoc support
 * @param mini Shell state
 * @param token Token containing the command
 * @return Execution result
 */
int	exec_logical_ops_heredoc(t_mini *mini, t_token *token)
{
	t_token	*next_op;
	int		ret;

	if (!token)
		return (0);
	next_op = find_next_logical_op(token);
	if (!next_op)
	{
		if (has_parentheses(token))
			return (exec_paren_with_redir_heredoc(mini, token));
		else
			return (check_string(mini, token));
	}
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
