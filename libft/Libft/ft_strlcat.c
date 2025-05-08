/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:30:19 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 16:21:57 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Copy  and  catenate  the  input string into a destination string.
 * If the destination buffer, limited by its size, isn't large enough to hold
 * the copy, the resulting string is truncated (but it is guaranteed to be 
 * null-terminated).
 * @param dst A pointer to the destination string.
 * @param src A pointer to the string 
 * @return The size of the final str;
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	dst_len;

	i = 0;
	dst_len = (ft_strlen(dst));
	if (ft_strlen(dst) >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (i + dst_len < dstsize - 1 && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (ft_strlen(src) + dst_len);
}
