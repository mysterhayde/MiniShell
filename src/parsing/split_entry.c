/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:51:45 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/21 16:40:29 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static unsigned int	word_len(char *str)
{
	int i;

	i = 0;
	while (str[i] && !is_separator(str[i]))
	{
		if (str[i] == '\'')
		{
			while (str[++i] && str[i] != '\'')
				;
		}
		else if (str[i] == '\"')
		{
			while (str[++i] && str[i] != '\"')
				;
		}
		i++;
	}
	return (i);
}

/**
 * @brief separates words according to bash syntax
 * @param char *str
 */
char *find_next_token(char *str, int *len)
{
	int		i;
	char	*splited;

	i = 0;
	*len = word_len(str);
	splited = malloc(sizeof(char) * (*len + 1));
	if (!splited)
		show_error("Malloc splited failed");
	while (i < *len)
	{
		splited[i] = str[i];
		i++;
	}
	splited[i] = '\0';
	return (splited);
}
