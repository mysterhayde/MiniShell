/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:51:17 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/22 02:51:05 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

static int	ft_strcmp_wildcard(char *s1, char *s2)
{
	int				i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (s1[i] && s2[i])
	{
		c1 = s1[i];
		c2 = s2[i];
		if (c1 >= 'A' && c1 <= 'Z')
			c1 += 32;
		if (c2 >= 'A' && c2 <= 'Z')
			c2 += 32;
		if (c1 != c2)
			break ;
		i++;
	}
	return (c1 - c2);
}

char	**sort_wildcard_tab(char **tab)
{
	int		j;
	int		i;
	int		pos;
	char	*temp;
	char	*min_str;

	i = -1;
	while (tab[++i])
	{
		j = i;
		pos = i;
		min_str = tab[i];
		while (tab[++j])
		{
			if (ft_strcmp_wildcard(tab[j], min_str) < 0)
			{
				min_str = tab[j];
				pos = j;
			}
		}
		temp = tab[i];
		tab[i] = tab[pos];
		tab[pos] = temp;
	}
	return (tab);
}
