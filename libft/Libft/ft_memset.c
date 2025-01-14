/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:49:33 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:55:39 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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