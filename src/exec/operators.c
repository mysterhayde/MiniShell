/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:24:36 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/25 16:54:09 by cbopp            ###   ########.fr       */
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
 * @brief Creates a sublist of tokens up to a logical operator
 * @param start start token
 * @param end end token (not included)
 * @return new token list
 */
t_token	*create_command_sublist(t_token *start, t_token *end)
{
	t_token	*current;
	t_token	*sublist;
	t_token *new_token;
	t_token	*last;

	sublist = NULL;
	last = NULL;
	current = start;
	while (current != end && current)
	{
		new_token = copy_token(current);
		if (!new_token)
			return (free_tokens(sublist), NULL);
		if (!sublist)
			sublist = new_token;
		else
			last->next = new_token;
		last = new_token;
		current = current->next;
	}
	return (sublist);
}
