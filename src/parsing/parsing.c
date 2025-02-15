/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/15 14:57:35 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			int i = 0;
			printf("%s	", token->cmd[i++]);
			printf(COLOR_GREEN"TYPE:	CMD\n"COLOR_RESET);
			while (token->cmd[i])
			{
				printf("%s	", token->cmd[i++]);
				printf(COLOR_YELLOW"TYPE:	ARG\n"COLOR_RESET);
			}
		}
		else if (token->type == PIPE)
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_RED"TYPE:	PIPE\n"COLOR_RESET);
		}
		else if (token->type == RDIT)
		{
			printf("%s	", token->cmd[0]);
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
	tab = split_args(str);
	while (tab[i])
	{
		allocate_tokens(tab[i], mini);
		i++;
	}
	//free_tab(tab);
	print_tokens(mini->backup); // Debug
	mini->token = mini->backup;
}
