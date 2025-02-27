/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:38:59 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/27 16:25:43 by hdougoud         ###   ########.fr       */
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

char	*clean_quote(char *str)
{
	char	*cleaned;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	cleaned = malloc(sizeof(char) * (strlen_quote(str) + 1));
	if (!cleaned)
		return (NULL); //print error
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\"' || str[i] == '\''))
			quote = str[i++];
		if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		cleaned[j++] = str[i++];
	}
	cleaned[j] = '\0';
	printf("%s\n", cleaned); //debug
	return (cleaned);
}
