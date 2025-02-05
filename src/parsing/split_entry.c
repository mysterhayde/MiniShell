/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:51:45 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/05 17:57:38 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_words(char const *str)
{
	unsigned int	i;
	unsigned int	word;

	word = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == 34 && str[i])
		{
			while (str[++i] != 34 && str[i])
				;
			word++;
		}
		i++;
		if (str[i] == ' ' && str[i])
		{	
			while (str[++i] == ' ' && str[i])
				;
			while(str[i] != ' ' && str[i])
				i++;
			word++;
		}
	}
	return (word);
}

// int		quote(char *str, int *i, char quote)
// {
// 	int		len;
// 	int		backup;
// 	char	*line;

// 	backup = *(i);
// 	len = 0;
// 	while(str[*(i)] || str[*(i)] == quote)
// 	{
// 		*(i)++;
// 		len++;
// 	}
// 	line = malloc(sizeof(char) * len);
// 	if (!line)
// 	{
// 		show_error("malloc failed");
// 		return NULL;
// 	}
// }

char	**split_args(char *str)
{
	char **tab;
	(void) *str;
	printf("%d Word\n", count_words(str));
	tab = malloc(sizeof(char *) * 2);
	tab[0] = ft_strdup("Hello");
	tab[1] = NULL;
	char c = 34;
	char dc = 39;
	printf("simple %c	double %c\n", dc, c);
	return (tab);
	// int		i;
	// int		j;
	// char	**split;

	// i = 0;
	// j = 0;
	// str = ft_strtrim(str, " ");
	// split = malloc(sizeof(char *) * (count_word(str) + 1));
	// while(str[i])
	// {
	// 	if (str[i] == 27)
	// 		tab[j] quote_len(str, split[j], )
	// 	if (!tab[j])
	// 	{
	// 		free_tab(split);
	// 		return (NULL)
	// 	}
	// }
	
	// split = NULL;
	// return (split);
}
