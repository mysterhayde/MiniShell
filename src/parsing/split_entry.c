/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:51:45 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/20 11:34:13 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static unsigned int	next_word_len(char *str, int i)
{
	while (str[i] && !is_separator(str[i]))
	{
		if (str[i] == '\'')
		{
			while (str[++i] && str[i] != '\'')
				;
		}
		if (str[i] == '\"')
		{
			while (str[++i] && str[i] != '\"')
				;
		}
		i++;
	}
	printf("i		%d\n", i);
	return (i);
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
		str = ft_strtrim(str, " \n\t");
		word_len = next_word_len(str, 0);
		split[++j] = malloc(sizeof(char) * (word_len + 1));
		if (!split[j])
			return (NULL);
		while (word_len > 0)
		{
			split[j][i++] = *str++;
			word_len--;
		}
		split[j][i] = '\0';
		word--;
	}
	split[++j] = NULL;
	return ((split));
}

static int	count_words(char const *str, unsigned int i, unsigned int word)
{
	while (str[i])
	{
		while (str[i] && is_separator(str[i]))
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
	printf("words	%d\n", word);
	return (word);
}

/**
 * @brief separates words according to bash syntax
 * @param char *str
 */
char	**split_args(char *str)
{
	int		word;
	char	**split;

	word = count_words(str, 0, 0);
	split = malloc(sizeof(char *) * (word + 1));
	if (!split)
		return (NULL);
	split = separate_args(split, str, word);
	return (split);
}
