/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:06 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/24 15:22:18 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Check if the token list contains logical ops
 * @param token token list to check
 * @return true if logical ops are present, false otherwise
 */
t_bool	has_logical_ops(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == AND_OP || current->type == OR_OP)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

/**
 * @brief Check if first token is a parenthesis
 * @param token Token to check
 * @return TRUE if token is LEFT_PAREN, FALSE otherwise
 */
t_bool	is_parenthesis_cmd(t_token *token)
{
	if (!token)
		return (FALSE);
	return (token->type == LEFT_PAREN);
}

/**
 * @brief Execute the command after a logical operator
 * @param mini Shell state
 * @param op Logical operator token
 * @param ret Return value from previous command
 * @return New return value
 */
int	process_remaining_cmds(t_mini *mini, t_token *tokens,
	t_bool condition)
{
	t_state	state;
	int		ret;

	if (!tokens || !condition)
		return (mini->ret);
	save_exec_state(mini, &state);
	mini->token = tokens;
	if (is_parenthesis_cmd(tokens))
		ret = exec_parenthesis(mini);
	else if (has_logical_ops(tokens))
		ret = exec_logical_ops(mini, tokens);
	else
		ret = exec_redirections_with_heredoc(mini, tokens);
	restore_exec_state(mini, &state);
	return (ret);
}

/**
 * @brief Execute parenthesis command and handle following tokens
 * @param mini Shell state
 * @return Execution result
 */
int	exec_parenthesis(t_mini *mini)
{
	t_token	*closing;
	t_token	*next_op;
	int		ret;

	ret = exec_paren_with_redir_heredoc(mini, mini->token);
	closing = find_matching_paren(mini->token);
	if (!closing || !closing->next)
		return (ret);
	next_op = find_next_logical(closing->next);
	if (!next_op)
		return (ret);
	if (next_op->type == AND_OP)
		ret = process_remaining_cmds(mini, next_op->next, ret == 0);
	else if (next_op->type == OR_OP)
		ret = process_remaining_cmds(mini, next_op->next, ret != 0);
	return (ret);
}

/**
 * @brief Reset processed flags on all heredoc tokens
 * @param token Starting token of the list
 */
void	reset_heredoc_processed_flags(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == HERE_DOC)
			current->processed = FALSE;
		current = current->next;
	}
}
