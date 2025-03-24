/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:36:04 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/24 16:37:52 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**add_cmd(char **tab, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab && tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (show_err_msg("Malloc", "failed"), NULL);
	i = 0;
	while (tab && tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = ft_strdup(str);
	if (!new_tab[i])
		return (show_err_msg("Malloc", "failed"), free_tab(new_tab), NULL);
	new_tab[i + 1] = NULL;
	return (safe_free((void **) &tab), new_tab);
}

char	**read_dir(char *pwd, int args, char *wildcard)
{
	DIR				*dir;
	struct dirent	*file;
	char			**files_tab;

	files_tab = NULL;
	dir = opendir(pwd);
	if (!dir)
		return (NULL);
	while (1)
	{
		file = readdir(dir);
		if (file == NULL)
			break ;
		if (args == 0
			|| compare_wildcard_and_file(file->d_name, wildcard))
		{
			if (file->d_name[0] == '.')
				continue ;
			files_tab = add_cmd(files_tab, file->d_name);
			if (!files_tab)
				return ((closedir(dir)), NULL);
		}
	}
	return (closedir(dir), files_tab);
}
