/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:13:16 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/28 16:23:34 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief search for the first occurrence of needle in haysatck
 * @param haystack the string to search
 * @param needle the substring to find
 * @param len The maximum number of characters to be examined in haystack
 * @return a pointer to the first occurrence found, otherwise finds NULL
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	count;
	unsigned int	needle_len;

	count = 0;
	needle_len = ft_strlen(needle);
	i = 0;
	if (needle_len == 0)
		return ((char *) haystack);
	while (haystack[i] != '\0' && len > i)
	{
		if (haystack[i] == needle [count])
			count++;
		else
		{
			i -= count;
			count = 0;
		}
		i++;
		if (needle_len == count)
			return ((char *) &haystack[i - count]);
	}
	return (NULL);
}

//int main(void)
//{
//    char *s1 = "lorem ipsum dolor sit amet";
//	char *s2 = "ipsum";
//    size_t max = strlen(s1);
//    //printf("%s\n", strnstr(s1, s2, 9));
//    printf("%s\n", ft_strnstr(s1, s2, 20));
//    return 0;
//}