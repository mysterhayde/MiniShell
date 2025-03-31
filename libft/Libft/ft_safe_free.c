/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:17:39 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/31 11:50:32 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief check and free safely
 * @param ptr give the adress of the pointer
 * @details exemple : (safe_free((void**)&str));
 */
void	safe_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	safe_free_tab(void ***ptr)
{
	int	i;

	i = 0;
	while ((*ptr)[i])
	{
		free((*ptr)[i]);
		(*ptr)[i++] = NULL;
	}
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}
