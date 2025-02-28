/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:36:04 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/28 16:25:08 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief search and returns a pointer to the first matching char from the end
 * @param s the string you want to search
 * @param c the char you want to find in *s
 * @return returns a pointer to the first char found, otherwise finds NULL
 */
char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	s = s + i;
	if (c == '\0')
		return ((char *) s);
	while (i >= 0)
	{
		if (*s == (char) c)
			return ((char *) s);
		s--;
		i--;
	}
	return (NULL);
}

//int main(void)
//{
//	char s[] = "Hello World this is a TestA";
//	printf("%s\n", ft_strrchr(s, 'A'));
//}