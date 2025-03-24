/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:10 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/24 16:18:30 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	last_segment(char *wildcard)
{
	int	i;
	
	i = 0;
	while (wildcard[i] && wildcard[i] != '*')
		i++;
	if (!wildcard[i])
		return (1);
	if (!wildcard[i + 1])
		return (1);
	return (0);
	
}

static int	segment_len(const char *str)
{
	int i;
	
	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	return (i);
}

int	check_first_segment(char *file, char **wildcard)
{
	int segment;

	if (**wildcard == '*')
	{
		*(wildcard) += 1;
		return (1);
	}
	segment = segment_len(*wildcard);
	if (strncmp(*wildcard, file, segment))
		return (0);
	return (1);
}

int check_last_segment(char *file, char *wildcard)
{
	int	segment;

	segment = segment_len(wildcard);
	if (wildcard[segment] == '*')
		return(0);
	while (*file)
	{
		if (!ft_strcmp(file, wildcard))
			return (0);
		file++;
	}
	return (1);
}

int	compare_wildcard_and_file(char *file, char *wildcard)
{
	int	segment;

	if (!check_first_segment(file, &wildcard))
		return (0);
	while (*file && *wildcard && !last_segment(wildcard))
	{
		while (wildcard && *wildcard == '*')
			wildcard++;
		segment = segment_len(wildcard);
		if (strncmp(wildcard, file, segment))
			file++;
		else
		{
			file += segment;
			wildcard += segment;
		}
	}
	if (check_last_segment(file, wildcard))
		return (0);
	return (1);
}
