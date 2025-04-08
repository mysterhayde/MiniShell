/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subchain_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:08:16 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/08 23:53:14 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_subchain	*new_subchain(char *str)
{
	t_subchain	*chain;

	chain = malloc(sizeof(t_subchain));
	if (!chain)
		return (NULL);
	
}

char	*subchain_system(char *str)
{
	int			i;
	t_subchain	first;

	i = 0;
	while (str[i]) //before check string sperate all in subchain and expand / remove quote if necessary
}