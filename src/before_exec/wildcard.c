/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:21 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/26 21:38:10 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**add_prefix(char **tab, char *prefixe)
{
	int		i;
	char	*new_file;

	i = 0;
	while (tab[i])
	{
		new_file = ft_strjoin(prefixe, tab[i]);
		if (!new_file)
			return (NULL);
		free(tab[i]);
		tab[i] = new_file;
		i++;
	}
	return (tab);
}

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
	int		args;
	char	**new_tab;

	i = -1;
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
	new_tab = combine_utils(new_tab, wildcard_tab, &i, 0);
	if (!new_tab)
		return (NULL);
	new_tab = combine_utils(new_tab, cmd, &i, k + 1);
	if (!new_tab)
		return (NULL);
	new_tab[i] = NULL;
	safe_free_tab((void ***)&cmd);
	return (safe_free_tab((void ***)&wildcard_tab), new_tab);
}

static char	**wildcard(char **cmd, char *wildcard, int i)
{
	int		args;
	char	*cwd;
	char	*prefix;
	char	**files;
	char	**result;

	args = 1;
	prefix = NULL;
	cwd = get_directory(&wildcard, &prefix);
	if (!cwd)
		return (NULL);
	if (!ft_strcmp(wildcard, "*"))
		args = 0;
	files = read_dir(cwd, args, wildcard);
	safe_free((void **)&wildcard);
	if (!files)
		return (safe_free((void **)&cwd), cmd);
	files = sort_wildcard_tab(files);
	if (prefix)
		if (add_prefix(files, prefix) == NULL)
			return (safe_free((void **)&prefix), free(cwd), NULL);
	safe_free((void **)&prefix);
	result = combine_tabs(cmd, files, i);
	return (safe_free((void **)&cwd), result);
}

char	**search_wildcard(t_token *token)
{
	int		i;
	char	*wildcard_cpy;

	i = 0;
	while (token->cmd[i])
	{
		if (search_wildcard_char(token->cmd[i]))
		{
			wildcard_cpy = ft_strdup(token->cmd[i]);
			if (!wildcard_cpy)
				return (show_err_msg("Malloc", "Allocation failed"), NULL);
			token->cmd = wildcard(token->cmd, wildcard_cpy, i);
			if (!token->cmd)
				return (show_err_msg("wildcard", "Wildcard failed"), NULL);
			safe_free((void **)&wildcard_cpy);
		}
		i++;
	}
	return (token->cmd);
}
