/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:48:27 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/05 11:23:47 by cbopp            ###   ########.fr       */
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
t_token	*find_next_op_with_parens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == LEFT_PAREN)
			current = skip_paren_expr(current);
		else if (current->type == AND_OP || current->type == OR_OP)
			return (current);
		else
			current = current->next;
		if (!current)
			break ;
	}
	return (NULL);
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
	int		ret;

	if (!token)
		return (1);
	if (token->type == LEFT_PAREN)
	{
		ret = exec_paren_expr(mini, token);
		if (!token->next)
			return (ret);
		op = token->next;
		if ((op->type == AND_OP && ret == 0)
			|| (op->type == OR_OP && ret != 0))
			return (exec_logical_op_with_parens(mini, op->next));
		return (ret);
	}
	op = find_next_logical_op(token);
	if (!op)
		return (exec_sublist(mini, token));
	sublist = create_command_sublist(token, op);
	if (!sublist)
		return (1);
	ret = exec_sublist(mini, sublist);
	free_tokens(sublist);
	if (op->type == AND_OP)
	{
		if (ret == 0)
			return (exec_logical_op_with_parens(mini, op->next));
		return (ret);
	}
	else if (op->type == OR_OP)
	{
		if (ret != 0)
			return (exec_logical_op_with_parens(mini, op->next));
		return (ret);
	}
	return (ret);
}
