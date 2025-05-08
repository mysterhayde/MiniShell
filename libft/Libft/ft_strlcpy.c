/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:02:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 16:21:51 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Copy  the  input string into a destination string.
 * If the destination buffer, limited by its size, isn't large enough to hold
 * the copy, the resulting string is truncated (but it is guaranteed to be 
 * null-terminated).
 * @param dst A pointer to the destination string.
 * @param src A pointer to the string 
 * @return The size of the final str;
 */
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