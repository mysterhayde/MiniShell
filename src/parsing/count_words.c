/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:28:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/10 11:39:58 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_words(char const *str)
{
	unsigned int	i;
	unsigned int	word;

	word = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == 34)
		{
			while (str[++i] != 34 && str[i])
				;
			word++;
		}	
		while(str[i] == ' ' && str[i])
				i++;
		if (str[i] && str[i] != ' ')
		{
			while (str[i] && str[i] != ' ')
				i++;
			word++;
		}
	}
	return (word);
}