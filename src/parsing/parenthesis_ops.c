/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:48:27 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/05 20:05:16 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Skip to the token after a parenthesized expression
 * @param token Starting token (LEFT_PAREN)
 * @return Token after the matching RIGHT_PAREN, NULL if no match
 */
t_token	*skip_paren_expr(t_token *token)
{
	t_token	*closing;

	if (!token || token->type != LEFT_PAREN)
		return (NULL);
	closing = find_matching_paren(token);
	if (!closing)
		return (NULL);
	return (closing->next);
}

/**
 * @brief Find next logical operator, respecting parentheses
 * @param token Token to start from
 * @return Token containing logical operator or NULL
 */
t_token	*find_next_logical_op_with_parens(t_token *token)
{
	t_token	*current;
	int		paren_depth;

	current = token;
	paren_depth = 0;
	while (current)
	{
		if (current->type == LEFT_PAREN)
			paren_depth++;
		else if (current->type == RIGHT_PAREN)
			paren_depth--;
		else if (paren_depth == 0 && (current->type == AND_OP
				|| current->type == OR_OP))
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * @brief Execute command that comes after a logical operator
 * @param mini Shell state
 * @param op Operator token
 * @param ret Return value of previous command
 * @return Execution result
 */
static int	exec_after_op(t_mini *mini, t_token *op, int ret)
{
	t_state	state;
	int		new_ret;

	if (!op || !op->next)
		return (ret);
	save_exec_state(mini, &state);
	if (op->type == AND_OP && ret == 0)
		new_ret = exec_logical_op_with_parens(mini, op->next);
	else if (op->type == OR_OP && ret == 0)
		new_ret = exec_logical_op_with_parens(mini, op->next);
	else
		new_ret = ret;
	restore_exec_state(mini, &state);
	return (new_ret);
}

/**
 * @brief Handle execution of parenthesized expression
 * @param mini Shell state
 * @param token Token starting with LEFT_PAREN
 * @return Execution result
 */
static int	handle_paren_expr(t_mini *mini, t_token *token)
{
	int		ret;
	t_token	*closing;
	t_token	*op;

	ret = exec_paren_expr(mini, token);
	closing = find_matching_paren(token);
	if (!closing)
		return (ret);
	if (!closing->next)
		return (ret);
	op = closing->next;
	if (op->type == AND_OP || op->type == OR_OP)
		return (exec_after_op(mini, op, ret));
	return (ret);
}

/**
 * @brief Execute a command with logical operators and parentheses
 * @param mini Shell state
 * @param token Token containing the command
 * @return Exit status
 */
int	exec_logical_op_with_parens(t_mini *mini, t_token *token)
{
	t_token	*op;
	t_token	*sublist;
	t_state	state;
	int		ret;

	if (!token)
		return (1);
	if (token->type == LEFT_PAREN)
		return (handle_paren_expr(mini, token));
	op = find_next_logical_op_with_parens(token);
	if (!op)
		return (exec_sublist(mini, token));
	sublist = create_command_sublist(token, op);
	if (!sublist)
		return (1);
	save_exec_state(mini, &state);
	ret = exec_sublist(mini, sublist);
	restore_exec_state(mini, &state);
	free_tokens(sublist);
	return (exec_after_op(mini, op, ret));
}
