/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:26:35 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/06 21:56:55 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Check if token is a redirection
 * @param token Token to check
 * @return True if redirection, FALSE otherwise
 */
static t_bool	is_redirection(t_token *token)
{
	if (!token)
		return (FALSE);
	return (token->type == RDIT && token->next->type == FILES);
}

/**
 * @brief Find the next logical operator after token
 * @param token Starting token
 * @return Logical operator token or NULL
 */
t_token	*find_next_logical(t_token *token)
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
 * @brief Applies redirections for a parenthesized expression
 * @param token Parenthesis token
 * @return 0 on success, 1 on failure
 */
int	apply_paren_redirections(t_token *token)
{
	t_token	*post_token;
	t_token	*current;
	t_token	*next_op;
	t_token	*closing;

	closing = find_matching_paren(token);
	if (!closing || !closing->next)
		return (0);
	post_token = closing->next;
	next_op = find_next_logical(post_token);
	current = post_token;
	while (current && (!next_op || current != next_op))
	{
		if (is_redirection(current))
		{
			if (process_single_redir(current) != 0)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
