/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:21 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/24 16:47:30 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**combine_utils(char **cmd_dest, char **cmd_src, int *pos, int j)
{
	int	i;

	i = *(pos);
	while (cmd_src[j])
	{
		cmd_dest[i] = ft_strdup(cmd_src[j++]);
		if (!cmd_dest[i++])
			return (NULL);
	}
	*(pos) = i;
	return (cmd_dest);
}

static char	**combine_tabs(char **cmd, char **wildcard_tab, int k)
{
	int		i;
	int		j;
	int		args;
	char	**new_tab;

	i = -1;
	j = 0;
	args = (ft_tablen(cmd) - 1) + ft_tablen(wildcard_tab);
	new_tab = malloc(sizeof(char *) * (args + 1));
	if (!new_tab)
		return (NULL);
	while (++i < k)
	{
		new_tab[i] = ft_strdup(cmd[i]);
		if (!new_tab[i])
			return (free_tab(new_tab), NULL);
	}
	new_tab = combine_utils(new_tab, wildcard_tab, &i, j);
	if (!new_tab)
		return (NULL);
	new_tab = combine_utils(new_tab, cmd, &i, k + 1);
	if (!new_tab)
		return (NULL);
	new_tab[i] = NULL;
	return (free_tab(cmd), new_tab);
}

char	**wildcard(char *pwd, char **cmd, char *wildcard, int i)
{
	int		args;
	char	**files;
	char	**result;

	if (!ft_strcmp(wildcard, "*"))
		args = 0;
	else
		args = 1;
	files = read_dir(pwd, args, wildcard);
	if (!files)
		return (cmd);
	files = sort_wildcard_tab(files);
	result = combine_tabs(cmd, files, i);
	return (free_tab(files), result);
}

char	**search_wildcard(t_token *token)
{
	int		i;
	char	current_path[PATH_MAX + 1];

	i = 0;
	while (token->cmd[i])
	{
		if (getcwd(current_path, PATH_MAX) == NULL)
			return (show_err_msg("getcwd", "getcwd failed"), NULL);
		if (search_wildcard_char(token->cmd[i]))
		{
			token->cmd = wildcard(current_path, token->cmd, token->cmd[i], i);
			if (!token->cmd)
				return (show_err_msg("wildcard", "wildcard failed"), NULL);
		}
		i++;
	}
	return (token->cmd);
}
