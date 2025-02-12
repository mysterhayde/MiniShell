/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/12 19:30:32 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

/**
 * @brief add a node to the end of the linked list
 * @param char *str
 * @param t_mini *mini
 * @param int type
 */
static void	add_last_token(char *str, t_mini *mini, int type)
{
	if (!mini->token)
	{
		mini->backup = malloc(sizeof(t_token));
		mini->token = new_token(str, type);
		if (!mini->token)
		{
			show_error("Malloc backup failed");
			exit(EXIT_FAILURE);
		}
		mini->backup = mini->token;
		return ;
	}
	while (mini->token->next)
		mini->token = mini->token->next;
	mini->token->next = new_token(str, type);
	mini->token = mini->token->next;
}

static void	allocate_tokens(char *str, t_mini *mini)
{
	int		op;

	op = is_operator(mini, str);
	if (op == 1)
	{
		add_last_token(str, mini, PIPE);
		mini->is_pipe = TRUE;
		mini->pipe_num++;
	}
	else if (op == 2)
		add_last_token(str, mini, RDIT);
	else if (mini->token == NULL || mini->token->type == PIPE
		|| mini->token->type == RDIT)
		add_last_token(str, mini, CMD);
	else if (mini->token->type == CMD || mini->token->type == ARG)
		add_last_token(str, mini, ARG);
}

static void	print_tokens(t_token *token)			// Debug function
{
	while (token)
	{
		if (token->type == CMD)
		{
			printf("%s	", token->str);
			printf(COLOR_YELLOW"TYPE:	CMD\n"COLOR_RESET);
		}
		else if (token->type == ARG)
		{
			printf("%s	", token->str);
			printf(COLOR_GREEN"TYPE:	ARG\n"COLOR_RESET);
		}
		else if (token->type == PIPE)
		{
			printf("%s	", token->str);
			printf(COLOR_RED"TYPE:	PIPE\n"COLOR_RESET);
		}
		else if (token->type == RDIT)
		{
			printf("%s	", token->str);
			printf("TYPE:	REDIRECTION\n");
		}
		token = token->next;
	}
}

/**
 * @brief parse entry in different tokens and distribute 
 * 		  them in the right categories.
 * @param char *str
 * @param t_mini *mini
 */
void	parsing(char *str, t_mini *mini)
{
	int		i;
	char	**tab;

	i = 0;
	mini->pipe_num = 0;
	mini->is_pipe = FALSE;
	if (str == NULL)
		return ;
	mini->token = NULL;
	tab = split_args(str);
	mini->debug = malloc(sizeof(t_debug));
	mini->debug->cmd = tab;
	while (tab[i])
	{
		allocate_tokens(tab[i], mini);
		i++;
	}
	print_tokens(mini->backup); // Debug
	mini->token = mini->backup;
}
