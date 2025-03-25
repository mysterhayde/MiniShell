/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_getdir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:46:24 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/25 13:56:08 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	pathlen(char *wildcard)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (wildcard[i])
	{
		if (wildcard[i] == '/')
			size = i + 1;
		i++;
	}
	return (size);
}

static int search_path(char **wildcard_src, char **path_src)
{
	int		i;
	int		size;
	char	*path;
	char	*wildcard;
	char	*temp;
	
	i = -1;
	path = NULL;
	wildcard = *wildcard_src;
	size = pathlen(wildcard);
	if (size)
	{		
		path = malloc(sizeof(char) * (size + 1));
		if (!path)
			return (-1);
		while (++i < size)
			path[i] = wildcard[i];
		path[i] = '\0';
	}
	*(path_src) = path;
	temp = ft_strdup(wildcard + size);
	if (!*wildcard)
		return (-1);
	*(wildcard_src) = temp;
	return (free(wildcard), 0);
}

char	*get_directory(char **wildcard, char **prefix)
{
	char	*cwd;									//if str[0] is a . add current path and add "./" before all file
	char	*path;
	char	*temp;
	char	current_path[PATH_MAX + 1];

	(void) cwd;
	path = NULL;
	*(prefix) = NULL;
	if (search_path(wildcard, prefix) == -1)
		return (NULL);
	if (*wildcard[0] == '/')
		return (path);
	if (getcwd(current_path ,PATH_MAX) == NULL)
		return (NULL);
	if (*(prefix) == NULL)
		return (ft_strdup(current_path));
	temp = ft_strjoin(current_path, "/");
	path = ft_strjoin(temp, *prefix);
	printf("%s\n", path);
	return (path);
}
