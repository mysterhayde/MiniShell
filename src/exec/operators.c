/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:24:36 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/06 22:09:41 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Finds the next logical operator in the token list
 * @param token token to start from
 * @return pointer to the logical operator or NULL
 */
t_token	*find_next_logical_op(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == AND_OP || current->type == OR_OP)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * @brief Executes a command with logical operators
 * @param mini shell state
 * @param token token containing the command
 * @return exit status
 */
int	exec_logical_ops(t_mini *mini, t_token *token)
{
	t_token	*op;
	t_token	*sublist;
	int		ret;

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
			return (exec_logical_ops(mini, op->next));
		return (ret);
	}
	else if (op->type == OR_OP)
	{
		if (ret != 0)
			return (exec_logical_ops(mini, op->next));
		return (ret);
	}
	return (ret);
}
