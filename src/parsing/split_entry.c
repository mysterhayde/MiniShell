/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:51:45 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/10 14:40:49 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static unsigned int	next_word_len(char *str)
{
	int	i;
	int	word_len;

	i = 0;
	word_len = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == 39)
		{
			while (str[++i] != 39 && str[i])
					word_len++;
			if (str[i + 1] == ' ')
			{
				word_len++;
				break ;
			}
		}
		i++;
		word_len++;
	}
	printf ("Word_len %d\n", word_len);		//debug
	return (word_len);
}

static char	**separate_args(char **split, char *str, int word)
{
	int	i;
	int	j;
	int	word_len;

	j = -1;
	while (word > 0)
	{
		i = 0;
		str = ft_strtrim(str, " ");
		word_len = next_word_len(str);
		split[++j] = malloc(sizeof(char) * (word_len + 1));
		if (!split[j])
			return (NULL);
		while (word_len > 0)
		{
			if (*str == 39)
				str++;
			split[j][i++] = *str++;
			word_len--;
		}
		split[j][i] = '\0';
		printf("%s\n", split[j]);
		word--;
	}
	split[j] = NULL;
	return (split);
}

char	**split_args(char *str)
{
	int		word;
	char	**split;

	word = count_words(str);
	printf ("Word count	%d\n", word);		//debug
	split = malloc(sizeof(char *) * (word + 1));
	if (!split)
		return (NULL);
	split = separate_args(split, str, word);
	return (split);
}
