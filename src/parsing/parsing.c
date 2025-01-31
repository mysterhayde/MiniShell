/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/31 18:20:47 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char	*parsing(char *str)
{
	int		i;
	char **tab;
	pid_t	pid;
	char	*bin;

	i = 0;
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		tab[i] = ft_strtrim(tab[i], " ");
		i++;
	}
	i = 0;
	bin = ft_strjoin("/bin/", tab[0]);
	pid = fork();
	if (pid == 0)
	{
		if (execve(bin, tab, NULL) == -1)
			show_error("commande not found");
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	free(bin);
	return (str);
}
