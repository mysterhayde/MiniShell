/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:08:22 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/05 11:12:55 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Find matchin closing parenthesis
 * @param token Token starting at an opening parenthesis
 * @return Pointer to matching closing parenthesis, NULL if not found
 */
t_token	*find_matching_paren(t_token *token)
{
	t_token	*current;
	int		depth;

	if (!token || token->type != LEFT_PAREN)
		return (NULL);
	current = token->next;
	depth = 1;
	while (current && depth > 0)
	{
		if (current->type == LEFT_PAREN)
			depth++;
		else if (current->type == RIGHT_PAREN)
			depth--;
		if (depth == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * @brief Check if token list contains parentheses
 * @param token Token list to check
 * @return TRUE if parentheses are present, FALSE otherwise
 */
t_bool	has_parentheses(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == LEFT_PAREN || current->type == RIGHT_PAREN)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

/**
 * @brief Execute expression within parentheses
 * @param mini Shell state
 * @param token Token list starting with LEFT_PAREN
 * @return Execution result
 */
int	exec_paren_expr(t_mini *mini, t_token *token)
{
	t_token	*closing;
	t_token	*sublist;
	int		ret;

	if (!token || token->type != LEFT_PAREN)
		return (1);
	closing = find_matching_paren(token);
	if (!closing)
	{
		show_err_msg("syntax error:", "unmatched parenthesis");
		return (1);
	}
	sublist = create_command_sublist(token->next, closing);
	if (!sublist)
		return (1);
	if (has_logical_ops(sublist))
		ret = exec_logical_ops(mini, sublist);
	else
		ret = exec_sublist(mini, sublist);
	free_tokens(sublist);
	return (ret);
}
