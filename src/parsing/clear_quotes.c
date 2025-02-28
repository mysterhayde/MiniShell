/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:38:59 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/28 12:44:26 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	strlen_quote(char *str)
{
	int i;
	int	quote;

	i = 0;
	quote = 0;
	while(str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
			quote += 2;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\"')
				i++;
			quote += 2;
		}
		i++;
	}
	return (i - quote);
}

char	*remove_quote(char *str, char *cleaned)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\"' || str[i] == '\''))
			quote = str[i++];
		if (str[i] == quote)
		{
			quote = 0;
			i++;
			continue ;
		}
		cleaned[j++] = str[i++];
	}
	cleaned[j] = '\0';
	return (free(str), cleaned);
}

char	*clean_quote(char *str)
{
	char	*cleaned;
	int		len;

	len = strlen_quote(str);
	cleaned = malloc(sizeof(char) * (len + 1));
	if (!cleaned)
		return (NULL);
	cleaned = remove_quote(str, cleaned);
	return (cleaned);
}
