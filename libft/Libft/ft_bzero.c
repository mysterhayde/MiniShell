/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:59:10 by hdougoud          #+#    #+#             */
/*   Updated: 2025/06/04 12:09:27 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief The ft_bzero() function erases the data in the n bytes of the memory
       starting at the location pointed to by s, by writing zeros (bytes  con‐
       taining '\0') to that area.
	@param s A pointer to the memory startng point.
	@param n The number of bytes of memory to replace by '\0'
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *) s;
	while (n > i)
	{
		ptr[i] = 0;
		i++;
	}
}

// int main(void)
// {
	// char s[] = "Hello World";
	// printf("%s\n", s);
	// ft_bzero(s, 6);
	// printf("%s\n", s);
	// return (0);
// }