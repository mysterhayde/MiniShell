/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:27:39 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:59:16 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 * The memory areas must not overlap.
 * @param dst A pointer to the destination.
 * @param src A pointer to the string to be copied to 'dst'.
 * @param n The number of bytes to copy.
 * @return A pointer to 'dst'.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*udst;
	unsigned char	*usrc;

	if (dst == NULL && src == NULL)
		return (0);
	udst = (unsigned char *) dst;
	usrc = (unsigned char *) src;
	i = 0;
	while (n > i)
	{
		udst[i] = usrc[i];
		i++;
	}
	return (dst);
}

//int main(void)
//{	
//	char s[] = "Hello World How Are You";
//	char se[] = "bjbjbjsbsnvsdndn kldf;lse";
//	printf("%s\n", se);
//	ft_memcpy(se, s, 20);
//	printf("%s\n", se);
//}