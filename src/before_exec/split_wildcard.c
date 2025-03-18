/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:24:57 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/17 14:46:58 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char **fill_wildcard_tab(char **tab, char *wildcard)
{
	int	i;
	int	j;

	j = 0;
	while(*wildcard)
	{
		i = 0;
		if (*wildcard == '*')
			wildcard++;
		while (wildcard[i] && wildcard[i] != '*')
			i++;
		tab[j] = malloc(sizeof(char) * (i + 1));
		if (!tab[j])
			return (NULL);
		ft_strlcpy(tab[j], wildcard, i + 1);
		j++;
		wildcard += i;
	}
	return (tab);
}

static int	count_wildcard_args(char *wildcard)
{
	int		i;
	int		args;

	i = 0;
	args = 0;
	while (wildcard[i])
	{
		if (wildcard[i] != '*')
		{
			args++;
			while (wildcard[i] && wildcard[i] != '*')
				i++;
			continue;
		}
		i++;
	}
	return (args);
}

int	split_wildcard(char *wildcard, char ***wildcard_tab)
{
	int		args;
	char	**tab;
	
	args = count_wildcard_args(wildcard);
	if (args == 0)
		return (0);
	tab = malloc(sizeof(char *) * (count_wildcard_args(wildcard) +1));
	if (!tab)
		return (-1);
	tab = fill_wildcard_tab(tab, wildcard);
	if (!tab)
		return (-1);
	*(wildcard_tab) = tab;
	return (1);
}
