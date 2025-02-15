/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayden <hayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:28:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/15 13:12:19 by hayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_words(char const *str, unsigned int i, unsigned int word)
{
	while (str[i])
	{
		if (is_separator(str[i]))
		{
			i++;
			continue ;
		}
		while (str[i] && !is_separator(str[i]))
		{
			if (str[i] == '\'')
				while (str[++i] != '\'' && str[i])
					;
			if (str[i] == '\"')
				while (str[++i] != '\"' && str[i])
					;
			if (!is_separator(str[i]))
				i++;
		}
		word++;
	}
	printf("Word count: %d\n", word);
	return (word);
}
