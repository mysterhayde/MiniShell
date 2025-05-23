/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:24:41 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/11 14:34:09 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	skip_until_next_quote(char *str, char quote, int i)
{
	int	j;
	int	double_quote;

	j = 0;
	double_quote = 0;
	while (j <= i)
	{
		if (str[j] == '\"')
			double_quote++;
		j++;
	}
	if ((double_quote % 2) != 0)
		return (1);
	return (find_next_quote(str + i, quote));
}

int	find_next_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i + 1);
}

/**
 * @brief Check if a string is an operator or parenthesis
 * @param mini Shell state
 * @param str String to check
 * @return Token type if operator/parenthesis, 0 otherwise
 */
int	is_operator(t_mini *mini, char *str)
{
	if (ft_strmincmp(str, "|", 1) == 0)
	{
		mini->is_pipe = TRUE;
		return (PIPE);
	}
	else if (ft_strmincmp(str, "<", 1) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, ">", 1) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, ">>", 2) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, "<<", 2) == 0)
		return (HERE_DOC);
	else if ((ft_strmincmp(str, "&&", 2) == 0))
		return (AND_OP);
	else if ((ft_strmincmp(str, "||", 2) == 0))
		return (OR_OP);
	else if (ft_strmincmp(str, "(", 1) == 0)
		return (LEFT_PAREN);
	else if (ft_strmincmp(str, ")", 1) == 0)
		return (RIGHT_PAREN);
	return (0);
}

/**
 * @brief Checks if the final token has valid syntax
 * @param token Final token
 * @return 0 if valid, 1 if not
 */
int	check_final_token(t_token *token)
{
	if (token->type == PIPE || token->type == AND_OP || token->type == OR_OP
		|| token->type == LEFT_PAREN)
		return (1);
	if (token->type != CMD && token->type != ARG && token->type != FILES
		&& token->type != LIMITER && token->type != RIGHT_PAREN)
		return (1);
	return (0);
}

/**
 * @brief Counts leading whitespace characters in a string
 * @param str String to check
 * @return Number of leading whitespace characters
 */
int	count_leading_spaces(char *str)
{
	int	spaces;

	spaces = 0;
	while (str[spaces] && (str[spaces] == ' '
			|| str[spaces] == '\n' || str[spaces] == '\t'))
		spaces++;
	return (spaces);
}
