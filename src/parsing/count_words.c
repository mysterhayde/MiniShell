/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:28:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/12 19:28:52 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_words(char const *str)
{
	unsigned int	i;
	unsigned int	word;

	word = 0;
	i = 0;
	while (str[i])
	{
		if (is_separator(str[i]))
			i++;
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
	return (word);
}
