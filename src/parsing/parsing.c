/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/09 15:32:06 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_syntax(t_token *token)
{
	int	last_type;

	last_type = 0;
	while (token->next)
	{
		if (last_type == 0 && (token->type != CMD
				&& token->type != RDIT && token->type != HERE_DOC))
			return (1);
		if ((last_type == PIPE || last_type == OR_OP || last_type == AND_OP)
			&& (token->type != CMD && token->type != RDIT))
			return (1);
		last_type = token->type;
		token = token->next;
	}
	if (token->type != CMD && token->type != ARG && token->type != FILES
		&& token->type != LIMITER)
		return (1);
	return (0);
}

static char	*allocate_tokens(char *str, t_mini *mini)
{
	if (!str)
		return (NULL);
	if (is_operator(mini, str) != 0)
		add_last_token(str, mini, is_operator(mini, str));
	else if (!mini->token)
		add_last_token(str, mini, CMD);
	else if (mini->token->type == RDIT)
		add_last_token(str, mini, FILES);
	else if (is_operator(mini, str) == HERE_DOC)
		add_last_token(str, mini, HERE_DOC);
	else if (mini->token->type == HERE_DOC)
		add_last_token(str, mini, LIMITER);
	else if (mini->token->type == CMD || mini->token->type == ARG)
		add_last_token(str, mini, ARG);
	else
		add_last_token(str, mini, CMD);
	if (!mini->token->cmd)
		return (NULL);
	return (str);
}

// static void	print_tokens(t_token *token)			// Debug function
// {
// 	while (token)
// 	{
// 		if (token->type == CMD)
// 		{
// 			printf("%s	", token->cmd[0]);
// 			printf(COLOR_GREEN"TYPE:	CMD");
// 			printf(COLOR_RESET"\n");
// 			for (int i = 1; token->cmd[i]; i++)
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
// 		else if (token->type == AND_OP)
// 		{
// 			printf("%s	", token->cmd[0]);
// 			printf(COLOR_RED"TYPE:	AND");
// 			printf(COLOR_RESET"\n");
// 		}
// 		else if (token->type == OR_OP)
// 		{
// 			printf("%s	", token->cmd[0]);
// 			printf(COLOR_RED"TYPE:	OR");
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
int	parsing(char *str, t_mini *mini)
{
	int		len;
	char	*next_token;

	mini->pipe_num = 0;
	mini->is_pipe = FALSE;
	next_token = str;
	while (*next_token)
	{
		next_token = ft_strtrim(next_token, " \n\t");
		if (next_token[0] == '#')
			break ;
		if (!allocate_tokens(find_next_token(next_token, &len), mini))
			return (EXIT_FAILURE);
		next_token += len;
	}
	// print_tokens(mini->backup); // Debug
	mini->token = mini->backup;
	if (check_syntax(mini->token))
		return (show_err_msg("Syntax Error", "unexpected token"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
