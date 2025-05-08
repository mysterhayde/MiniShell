/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:49:33 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 16:07:46 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Fills the first n bytes of the memory area pointed to by s with the
 * constant byte c.
 * @param b A pointer to the string to be manipulated
 * @param c The byte to fill the memory.
 * @param len The number of bytes to fill.
 */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*ptr;
	unsigned char	uc;

	uc = (unsigned char) c;
	ptr = (unsigned char *) b;
	i = 0;
	while (len > i)
	{
		ptr[i] = uc;
		i++;
	}
	return (b);
}

//int main()
//{
//	char ptr[] = "Hello World";
//	printf("%s\n", ptr);
//	ft_memset(ptr, 'Z', 4);
//	printf("%s\n", ptr);
//	return (0);
//}