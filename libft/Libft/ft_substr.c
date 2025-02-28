/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:36:33 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/28 16:42:59 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static unsigned int	ft_memorylen(char const *s, unsigned int start, size_t len)
{
	unsigned int	r;

	r = ft_strlen(s) - start;
	if (r < len)
		return (r);
	return (len);
}

/**
 * @brief Extracts a substring from a given string.
 * @param s The input string.
 * @param start The starting index in `s` from which to extract the substring.
 * @param len The maximum number of characters to extract.
 * @return A newly allocated string containing the extracted substring,
 * or NULL if the allocation fails or if `s` is NULL. 
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	str = malloc((ft_memorylen(s, start, len) + 1) * sizeof(char));
	if (str == 0)
		return (NULL);
	while (len > i && s[start] != '\0')
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

//int main(void)
//{
//	char s[] = "1234567";
//	printf("%s\n", ft_substr(s, 5, 4));
//	//printf("%s\n", substr(s, 10, 10));
//	return (0);
//}
