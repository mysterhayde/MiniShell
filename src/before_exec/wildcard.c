/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:21 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/19 15:33:29 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static int	tab_size(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

static char	**combine_tabs(char **cmd, char **wildcard_tab, int k)
{
	int		i;
	int		j;
	int		args;
	char	**new_tab;

	i = 0;
	j = 0;
	args = (tab_size(cmd) - 1) + tab_size(wildcard_tab);
	new_tab = malloc(sizeof(char *) * (args + 1));
	if (!new_tab)
		return (NULL);
	while(i < k)
	{
		new_tab[i] = ft_strdup(cmd[i]);
		if (!new_tab)
			return (free_tab(new_tab) ,NULL);
		i++;
	}
	while(wildcard_tab[j])
		new_tab[i++] = wildcard_tab[j++];
	while(cmd[++k])
	{
		new_tab[i++] = ft_strdup(cmd[k]);
		if (!new_tab)
			return (free_tab(new_tab) ,NULL);
	}
	new_tab[i] = NULL;
	return (free_tab(cmd), new_tab);
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

char	**wildcard(char *pwd, char **cmd, char *wildcard, int i)
{
	int				args;
	char			**wildcard_tab;

	wildcard_tab = NULL;
	//wildcard = clean_quote(wildcard);
	args = split_wildcard(wildcard, &wildcard_tab);
	if (args == -1)
		return (NULL);
	wildcard_tab = read_dir(pwd, wildcard_tab, args);
	if (!wildcard_tab)
		return (cmd); //check leak
	// sort files_tab
	cmd = combine_tabs(cmd, wildcard_tab, i);
	return (free_tab(wildcard_tab), cmd);
}

char **search_wildcard(t_token *token)
{
	int		i;
	char	current_path[PATH_MAX + 1];

	i = 0;
	while (token->cmd[i])
	{
		if (getcwd(current_path, PATH_MAX) == NULL)
			return (show_err_msg("getcwd", "getcwd failed") ,NULL);
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
