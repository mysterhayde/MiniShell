/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:21:41 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/21 11:09:34 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief malloc a pointer by setting everything to zero
 * @param size_t sizeof
 * @param size_t the quantity you want malloc
 */

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == 0)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

//int main(void)
//{
//	ft_calloc(2, 2);
//}