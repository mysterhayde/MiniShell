/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/25 14:45:19 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Checks if the current token has valid syntax
 * @param token Current token
 * @param last_type Previous token type
 * @return 0 if syntax is valid, 1 if not
 */
static int	check_token_syntax(t_token *token, int last_type)
{
	if (last_type == 0 && (token->type != CMD
			&& token->type != RDIT && token->type != HERE_DOC
			&& token->type != LEFT_PAREN))
		return (1);
	if ((last_type == PIPE || last_type == OR_OP || last_type == AND_OP)
		&& (token->type != CMD && token->type != RDIT
			&& token->type != LEFT_PAREN))
		return (1);
	if (last_type == LEFT_PAREN && token->type != CMD
		&& token->type != RDIT && token->type != HERE_DOC
		&& token->type != LEFT_PAREN)
		return (1);
	if (last_type == RIGHT_PAREN && token->type != PIPE
		&& token->type != AND_OP && token->type != OR_OP
		&& token->type != RIGHT_PAREN && token->type != CMD
		&& token->type != RDIT && token->type != HERE_DOC)
		return (1);
	return (0);
}

/**
 * @brief Allocates tokens based on their type
 * @param str String to allocate token for
 * @param mini Shell state
 * @return The allocated string or NULL on error
 */
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
	else if (mini->token->type == HERE_DOC)
		add_last_token(str, mini, LIMITER);
	else if (mini->token->type == PIPE || mini->token->type == AND_OP
		|| mini->token->type == OR_OP || mini->token->type == LEFT_PAREN
		|| !mini->last_cmd)
		add_last_token(str, mini, CMD);
	else
		add_last_token(str, mini, ARG);
	if (!mini->token->cmd)
		return (NULL);
	return (str);
}

static void	print_tokens(t_token *token)			// Debug function
{
	while (token)
	{
		if (token->type == CMD)
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_GREEN"TYPE:	CMD");
			printf(COLOR_RESET"\n");
			for (int i = 1; token->cmd[i]; i++)
			{
				printf("%s	", token->cmd[i]);
				printf(COLOR_GREEN_ULTRA"TYPE:	ARG");
				printf(COLOR_RESET"\n");
			}
		}
		else if (token->type == PIPE)
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_RED"TYPE:	PIPE");
			printf(COLOR_RESET"\n");
		}
		else if (token->type == RDIT)
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_BLUE"TYPE:	REDIRECTION");
			printf(COLOR_RESET"\n");
		}
		else if (token->type == FILES)
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_PURPLE"TYPE:	FILE");
			printf(COLOR_RESET"\n");
		}
		else if (token->type == HERE_DOC)
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_CYAN"TYPE:	HERE_DOC");
			printf(COLOR_RESET"\n");
		}
		else if (token->type == LIMITER)
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_CYAN"TYPE:	LIMITER");
			printf(COLOR_RESET"\n");
		}
		else if (token->type == AND_OP)
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_RED"TYPE:	AND");
			printf(COLOR_RESET"\n");
		}
		else if (token->type == OR_OP)
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_RED"TYPE:	OR");
			printf(COLOR_RESET"\n");
		}
		else if (token->type == LEFT_PAREN || token->type == RIGHT_PAREN)
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_YELLOW"TYPE:	PARENTHESE");
			printf(COLOR_RESET"\n");
		}
		else 
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_RED_ULTRA"TYPE:	UNKNOW");
			printf(COLOR_RESET"\n");
		}
		token = token->next;
	}
}

/**
 * @brief Checks token syntax and balancing of parentheses
 * @param token Token list to check
 * @return 0 if syntax is valid, 1 if not
 */
static int	check_syntax(t_token *token)
{
	t_token	*current;
	int		last_type;

	if (check_paren_balance(token))
		return (1);
	current = token;
	last_type = 0;
	while (current)
	{
		if (check_token_syntax(current, last_type))
			return (1);
		last_type = current->type;
		if (!current->next)
			break ;
		current = current->next;
	}
	if (check_final_token(current))
		return (1);
	return (0);
}

/**
 * @brief parse entry in different tokens and distribute 
 * 		  them in the right categories.
 * @param char *str
 * @param t_mini *mini
 * @returns EXIT_SUCCESS or EXIT_FAILURE
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
		ft_strtrim_nc(&next_token, " \t\n");
		if (!allocate_tokens(find_next_token(next_token, &len), mini))
			return (EXIT_FAILURE);
		next_token += len;
	}
	print_tokens(mini->backup); // Debug
	mini->token = mini->backup;
	if (check_syntax(mini->token))
		return (show_err_msg("Syntax Error", "unexpected token"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
