/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:21 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/17 11:59:59 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	search_wildcard(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while(str)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while(str[i] && str[i] != quote)
				i++;
			i++;
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

char	**wildcard(char *pwd, char **cmd)
{
	DIR				*dir;
	struct dirent	*file;

	dir = opendir(pwd);
	if (dir == NULL)
		return (NULL);
	while (1)
	{
		file = readdir(dir);
		if (file == NULL)
			break;
		printf("WILDCARD	%s\n", file->d_name);
		cmd = add_cmd(cmd, file->d_name);
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}
