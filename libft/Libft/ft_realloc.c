/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:12:17 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/05 18:12:57 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief realloc
 * @param void *ptr you want to realloc
<<<<<<< HEAD
 * @param size_t "sizeof(vartype) * size" to specify what 
 * 				type of size it needs to malloc
=======
 * @param size_t sizeof(vartype) * size" to specify what type 
 * 				 of size it needs to malloc
>>>>>>> parseur
 */
void	*ft_realloc(void *ptr, size_t size)
{
	void	*array;

	array = (void *)malloc(size);
	if (!array)
		return (NULL);
	ft_strlcpy(array, ptr, size);
	free(ptr);
	return (array);
}
