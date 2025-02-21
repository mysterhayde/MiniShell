/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:51:45 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/21 14:23:39 by hdougoud         ###   ########.fr       */
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
	printf(COLOR_PURPLE"NEXT_WORD_LEN 	%d\n"COLOR_RESET, i);
	return (i);
}

// static char	**separate_args(char **split, char *str, int word)
// {
// 	int	i;
// 	int	word_len;

// 		i = 0;
// 		str = ft_strtrim(str, " \n\t");
// 		word_len = next_word_len(str, 0);
// 		split[++j] = malloc(sizeof(char) * (word_len + 1));
// 		if (!split[j])
// 			return (NULL);
// 		while (word_len > 0)
// 		{
// 			split[j][i++] = *str++;
// 			word_len--;
// 		}
// 		split[j][i] = '\0';
// 		word--;
// 	return ((split));
// }

// static int	count_words(char const *str, unsigned int i, unsigned int word)
// {
// 	while (str[i])
// 	{
// 		while (str[i] && is_separator(str[i]))
// 			i++;
// 		while (str[i] && !is_separator(str[i]))
// 		{
// 			if (str[i] == '\'')
// 				while (str[++i] != '\'' && str[i])
// 					;
// 			if (str[i] == '\"')
// 				while (str[++i] != '\"' && str[i])
// 					;
// 			if (!is_separator(str[i]))
// 				i++;
// 		}
// 		word++;
// 	}
// 	printf("words	%d\n", word);
// 	return (word);
// }

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
