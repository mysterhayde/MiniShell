/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:02:22 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/08 09:49:21 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*find_last_token(t_token *token, int *paren)
{
	while (token->next)
	{
		if (token->type == LEFT_PAREN || token->type == RIGHT_PAREN)
			*(paren) = 1;
		token = token->next;
	}
	return (token);
}

static int	add_before_token(t_mini *mini)
{
	t_token	*first;

	first = malloc(sizeof(t_token));
	if (!first)
		return (1);
	first->cmd = malloc(sizeof(char *) * 2);
	if (!first->cmd)
		return (free(first), 1);
	first->cmd[0] = ft_strdup("(");
	if (!first->cmd[0])
		return (free(first->cmd), free(first), 1);
	first->cmd[1] = NULL;
	first->type = LEFT_PAREN;
	first->next = mini->backup;
	mini->backup = first;
	mini->token = mini->backup;
	return (0);
}

static int	add_back_token(t_mini *mini)
{
	t_token	*last;

	last = malloc(sizeof(t_token));
	if (!last)
		return (1);
	last->cmd = malloc(sizeof(char *) * 2);
	if (!last->cmd)
		return (free(last), 1);
	last->cmd[0] = ft_strdup(")");
	if (!last->cmd[0])
		return (free(last->cmd), free(last), 1);
	last->cmd[1] = NULL;
	last->type = RIGHT_PAREN;
	last->next = NULL;
	while (mini->token->next)
		mini->token = mini->token->next;
	mini->token->next = last;
	return (0);
}

int	check_parenthesis(t_mini *mini)
{
	int		have_paren;
	t_token	*last_token;

	have_paren = 0;
	last_token = find_last_token(mini->token, &have_paren);
	(void) last_token;
	if (have_paren == 0)
		return (0);
	if (add_before_token(mini))
		return (1);
	if (add_back_token(mini))
		return (1);
	return (0);
}
