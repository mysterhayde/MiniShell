/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:21 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/19 10:31:48 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	compare_wildcard(char **wildcard_tab, char *file)
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

static char	**add_cmd(char **cmd, char *str)
{
	int		i;
	char	**new_cmd;

	if (str[0] == '.')
		return (cmd);
	i = 0;
	while (cmd[i])
		i++;
	new_cmd = malloc(sizeof(char *) * (i + 2));
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	new_cmd[i] = ft_strdup(str);
	if (!new_cmd[i])
		return (free_tab(new_cmd), NULL);
	new_cmd[i + 1] = NULL;
	return (free(cmd), new_cmd);
}


char	**wildcard(char *pwd, char **cmd, char *wildcard)
{
	int				args;
	char			**wildcard_tab;
	DIR				*dir;
	struct dirent	*file;

	dir = NULL; //remove later
	wildcard_tab = NULL;
	//remove current wildcard character
	args = split_wildcard(wildcard, &wildcard_tab);
	if (args == -1)
		return (closedir(dir), NULL);
	if (args != 0)
	{
		for (int i = 0; wildcard_tab[i]; i++)
			printf("%s\n", wildcard_tab[i]);
	}
	dir = opendir(pwd);
	if (dir == NULL)
		return (NULL);
	while (1)
	{
		file = readdir(dir);
		if (file == NULL)
			break;
		if (args == 0 || compare_wildcard(wildcard_tab, file->d_name))
		{
			cmd = add_cmd(cmd, file->d_name);
			if (!cmd)
				return (NULL);
		}
	}
	free_tab(wildcard_tab);
	return (closedir(dir), cmd);
}
