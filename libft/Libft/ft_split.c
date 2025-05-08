/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:54:38 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 16:12:37 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_words(char const *s, char c)
{
	unsigned int	word;

	word = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
			word++;
		while ((*s != c && *s))
			s++;
	}
	return (word);
}

static void	ft_free_tab(char **tab, int j)
{
	while (j > 0)
		free(tab[--j]);
	free(tab);
}

static char	**ft_fill_tab(char const *s, char c, char **tab)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	while (*s)
	{
		i = 0;
		while (*s == c && *s)
			s++;
		if (*s)
		{
			while (s[i] != c && s[i])
				i++;
			tab[j] = ft_substr(s, 0, i);
			if (tab[j] == NULL)
			{
				ft_free_tab(tab, j);
				return (NULL);
			}
			s += i;
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

/**
 * @brief Splits a string, at every 'c', into a table of strings
 * @param s A pointer to the string to split.
 * @param c The character used to split the string.
 * @return A pointer to the table of strings.
 */
char	**ft_split(char const *s, char c)
{
	char			**tab;

	tab = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (tab == 0)
		return (NULL);
	return (ft_fill_tab(s, c, tab));
}

//int main(void)
//{
//	int 	i = 0;
//	int		nb = 0;
//	char	c = ' ';
//	char s[] = "  Hello    This is a             test"  ;
//	char **tab = ft_split(s, c);
//	while (tab[i] != NULL)
//	{
//		printf("%s\n", tab[i]);
//		i++;
//	}
//}