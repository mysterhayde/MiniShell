/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:02:05 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:56:10 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

//int main(void)
//{
//	char s[] = "lorem ipsum dolor sit amet";
//	char se[6] = "";
//	char sr[6] = "";
//	printf("%zu\n", ft_strlcpy(se, s, 5));
//	printf("%s\n", se);
//	printf("%zu\n", strlcpy(sr, s, 0));
//	printf("%s\n", sr);
//	return (0);
//}