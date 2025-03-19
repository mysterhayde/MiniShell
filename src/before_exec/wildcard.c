/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:21 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/19 11:57:05 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	compare_wildcard_and_file(char **wildcard_tab, char *file)
{
	char	*str;
	int		i;

	i = 0;
	str = file;
	while (wildcard_tab[i])
	{
		str = ft_strnstr(file, wildcard_tab[i], ft_strlen(str));
		if (!str)
			return (0);
		i++;
	}
	return (1);
}

int	search_wildcard_char(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while(str[i] && str[i] != quote)
				i++;
			i++;
			continue ;
		}
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

char	**wildcard(char *pwd, char **cmd, char *wildcard)
{
	int				args;
	char			**wildcard_tab;

	wildcard_tab = NULL;
	wildcard = clean_quote(wildcard);
	args = split_wildcard(wildcard, &wildcard_tab);
	if (args == -1)
		return (NULL);
	if (args != 0)
	{
		for (int i = 0; wildcard_tab[i]; i++)
			printf("%s\n", wildcard_tab[i]);
	}
	wildcard_tab = read_dir(pwd, cmd, wildcard_tab, args)
	if (!wildcard_tab)
	// sort files_tab
		
	// combine actual cmd_tab and files_tab && remove current wildcard caractere
	return (free_tab(wildcard_tab), cmd);
}
