/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:18:19 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:56:27 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = ft_strlen(s);
	str = malloc(sizeof(char) * i + 1);
	if (str == 0)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

//int main(void)
//{
//	char s[] = "Hello World";
//	printf("%s\n", ft_strmapi(s, &ft_test));
//}
//
//char ft_test(unsigned int n, char c)
//{
//	if (c >= 97 && c <= 122 && n < 8)
//		c = c - 32;
//	return (c);
//}