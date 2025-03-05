/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:28:56 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/05 20:02:41 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Print token list for debugging
 * @param prefix message prefix to identify the call
 * @param token starting token to print
 */
void	debug_print_tokens(char *prefix, t_token *token)
{
	t_token	*current;
	int		i;

	fprintf(stderr, "\n======= %s =======\n", prefix);
	current = token;
	while (current)
	{
		fprintf(stderr, "Token type: %d, ", current->type);
		if (current->cmd)
		{
			fprintf(stderr, "cmd: [");
			i = 0;
			while (current->cmd[i])
			{
				fprintf(stderr, "%s", current->cmd[i]);
				if (current->cmd[i + 1])
					fprintf(stderr, ", ");
				i++;
			}
			fprintf(stderr, "]\n");
		}
		else
			fprintf(stderr, "cmd: NULL\n");
		current = current->next;
	}
	fprintf(stderr, "=======================\n\n");
}
