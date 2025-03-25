/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_getdir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:46:24 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/25 13:01:49 by hdougoud         ###   ########.fr       */
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
	free(wildcard);
	*(wildcard_src) = temp;
	return (0);
}

char	*get_directory(char **wildcard, char **prefix) 	//if str[0] is a . add current path and add "./" before all file
{
	char	*cwd;
	char	*path;
	char	current_path[PATH_MAX + 1];

	(void) cwd;
	path = NULL;
	if (search_path(wildcard, prefix) == -1)
		return (NULL);
	printf("PREFIX %p\n", *prefix);
	if (*wildcard[0] == '/')
		return (path);
	if (getcwd(current_path ,PATH_MAX) == NULL)
		return (NULL);
	if (!prefix)
		return (ft_strdup(current_path));
	printf("Wildcard %s\n", *wildcard);
	printf("Prefix %p\n", *prefix);
	printf("PATH %s\n", path);
	return (path);
}