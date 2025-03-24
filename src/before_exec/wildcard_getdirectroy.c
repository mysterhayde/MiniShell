/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_getdirectroy.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:46:24 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/24 16:56:28 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *search_path(char *wildcard)
{
	int i;
	char *path;

	i = 0;
	while (wildcard[i])
	{
		if (wildcard[i] = '/')
			//add to path
	}
}

char *get_directory(char *pwd, char *wildcard)
{
	char *path;
	int i;

	i = 0;
	
}