/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:26:10 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/30 16:27:18 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Finds the next pipe token
 * @param token Starting token
 * @return Next pipe token or NULL
 */
t_token	*find_next_pipe_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == PIPE)
			return (current);
		current = current->next;
	}
	return (NULL);
}