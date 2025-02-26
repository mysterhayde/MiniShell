/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:11:15 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/26 11:45:06 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Frees all links in the token chain, as well 
 * 		  as the cmd array inside each node
 * @param t_mini *mini
 */
void	free_token_list(t_mini *mini)
{
	if (!mini->backup)
		return ;
	mini->token = mini->backup;
	while (mini->token)
	{
		mini->token = mini->token->next;
		free(mini->backup->str);
		free(mini->backup);
		mini->backup = mini->token;
	}
	mini->token = NULL;
	mini->backup = NULL;
}

/**
 * @brief Create a new node
 * @param char *str
 * @param int type
 * @return t_token node
 */
static t_token	*new_token(char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		show_error("Malloc token failed");
		exit(EXIT_FAILURE);
	}
	new->str = str;
	new->type = type;
	new->next = NULL;
	return (new);
}

static void	create_first_node(t_mini *mini, char *str, int type)
{
	mini->backup = malloc(sizeof(t_token));
	if (!mini->backup)
	{
		show_error("Malloc backup failed");
		exit(EXIT_FAILURE);
	}
	mini->token = new_token(str, type);
	if (!mini->token)
	{
		show_error("Malloc backup failed");
		exit(EXIT_FAILURE);
	}
	mini->backup = mini->token;
}

/**
 * @brief add a node to the end of the linked list
 * @param char *str
 * @param t_mini *mini
 * @param int type
 */
void	add_last_token(char *str, t_mini *mini, int type)
{
	if (!mini->token)
	{
		create_first_node(mini, str, type);
		return ;
	}
	while (mini->token->next)
		mini->token = mini->token->next;
	mini->token->next = new_token(str, type);
	mini->token = mini->token->next;
}
