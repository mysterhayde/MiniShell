/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/25 15:46:58 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	allocate_tokens(char *str, t_mini *mini)
{
	if (!mini->token)
		add_last_token(str, mini, CMD);
	else if (is_operator(mini, str) == PIPE)
		add_last_token(str, mini, PIPE);
	else if (is_operator(mini, str) == RDIT)
		add_last_token(str, mini, RDIT);
	else if (mini->token->type == RDIT)
		add_last_token(str, mini, FILES);
	else if (is_operator(mini, str) == HERE_DOC)
		add_last_token(str, mini, HERE_DOC);
	else if (mini->token->type == HERE_DOC)
		add_last_token(str, mini, LIMITER);
	else if (mini->token->type == CMD)
		add_last_token(str, mini, ARG);
	else
		add_last_token(str, mini, CMD);
}

// static void	print_tokens(t_token *token)			// Debug function
// {
// 	while (token)
// 	{
// 		if (token->type == CMD)
// 		{
// 			int i = 0;
// 			printf("%s	", token->cmd[i]);
// 			printf(COLOR_GREEN"TYPE:	CMD");
// 			printf(COLOR_RESET"\n");
// 			while (token->cmd[++i])
// 			{
// 				printf("%s	", token->cmd[i]);
// 				printf(COLOR_GREEN_ULTRA"TYPE:	ARG");
// 				printf(COLOR_RESET"\n");
// 			}
// 		}
// 		else if (token->type == PIPE)
// 		{
// 			printf("%s	", token->cmd[0]);
// 			printf(COLOR_RED"TYPE:	PIPE");
// 			printf(COLOR_RESET"\n");
// 		}
// 		else if (token->type == RDIT)
// 		{
// 			printf("%s	", token->cmd[0]);
// 			printf(COLOR_BLUE"TYPE:	REDIRECTION");
// 			printf(COLOR_RESET"\n");
// 		}
// 		else if (token->type == FILES)
// 		{
// 			printf("%s	", token->cmd[0]);
// 			printf(COLOR_PURPLE"TYPE:	FILE");
// 			printf(COLOR_RESET"\n");
// 		}
// 		else if (token->type == HERE_DOC)
// 		{
// 			printf("%s	", token->cmd[0]);
// 			printf(COLOR_CYAN"TYPE:	HERE_DOC");
// 			printf(COLOR_RESET"\n");
// 		}
// 		else if (token->type == LIMITER)
// 		{
// 			printf("%s	", token->cmd[0]);
// 			printf(COLOR_CYAN"TYPE:	LIMITER");
// 			printf(COLOR_RESET"\n");
// 		}
// 		token = token->next;
// 	}
// }

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
	if (tab == NULL)
		return (show_err_msg("malloc", "memory allocation failed"));
	while (tab[i])
	{
		allocate_tokens(tab[i], mini);
		i++;
	}
	//free_tab(tab);  //already freed ??
	//print_tokens(mini->backup); // Debug
	mini->token = mini->backup;
}
