/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:51:45 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/04 16:08:16 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_args(char *str)
{
	int		j;
	char	**split;

	j = 0;
	split = ft_split(str, ' ');
	while (split[j])
	{
		split[j] = ft_strtrim(split[j], " ");
		j++;
	}
	
	int		debug;
	while (split[debug])
		printf("%s\n", split[debug++]);
	return (split);
}
