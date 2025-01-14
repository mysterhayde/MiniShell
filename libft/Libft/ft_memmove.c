/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:21:28 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:55:37 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*udst;
	unsigned char	*usrc;

	udst = (unsigned char *) dst;
	usrc = (unsigned char *) src;
	if (dst == NULL && src == NULL)
		return (0);
	if (src < dst)
	{
		while (len >= 1)
		{
			udst[len - 1] = usrc[len - 1];
			len --;
		}
	}
	else
		return (ft_memcpy(dst, src, len));
	return (dst);
}

//int main(void)
//{
//	char s[] = "lorem";
//	char se[] = "aaaaaaaaaaaa";
//	printf("Original %s\n", memmove(se, s , '\0'));
//	char s1[] = "lorem";
//	char se1[] = "aaaaaaaaaaaa";
//	printf("42	 %s\n", ft_memmove(se1, s1 , '\0'));
//}