/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:51:45 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/05 20:04:14 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_next_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i + 1);
}

static int	is_separator(char *str)
{
	if (str[0] == ' ' || str[0] == '\t' || str[0] == '\n')
		return (1);
	else if (str[0] == '(' || str[0] == ')')
		return (1);
	else if ((str[0] == '<' || str[0] == '>' || str[0] == '|')
		&& (str[0] != str[1]))
		return (1);
	else if ((str[0] == '<' || str[0] == '>' || str[0] == '&' || str[0] == '|')
		&& str[0] == str[1])
		return (2);
	return (0);
}

static unsigned int	word_len(char *str)
{
	int	i;
	int	quote;

	i = 0;
	while (str[i])
	{
		if (is_separator(str + i))
		{
			if (i == 0)
				return (is_separator(str));
			break ;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = find_next_quote(str + i, str[i]);
			if (quote == -1)
				return (-1);
			i += quote;
			continue ;
		}
		i++;
	}
	return (i);
}

/**
 * @brief separates words according to bash syntax
 * @param str string to split
 * @param len length of the token (set by this function)
 * @return next token or NULL on error
 */
char	*find_next_token(char *str, int *len)
{
	int		i;
	char	*splited;

	i = 0;
	*len = word_len(str);
	if (*len == -1)
		return (show_err_msg("syntax error", "quote not closed"), NULL);
	splited = malloc(sizeof(char) * (*len + 1));
	if (!splited)
		return (show_err_msg("malloc", "malloc allocation failed"), NULL);
	while (i < *len)
	{
		splited[i] = str[i];
		i++;
	}
	splited[i] = '\0';
	return (splited);
}
