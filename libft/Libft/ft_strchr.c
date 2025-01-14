/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:11:44 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:55:54 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}

//int main(void)
//{
//	char s[] = "Hello World this is a test";
//	int res = 1;
//    printf("ft_strnchr	%s\n", ft_strchr("teste", 't'));
//    printf("ft_strnchr	%s\n", ft_strchr("teste", 'e'));
//    printf("ft_strnchr	%s\n", ft_strchr("teste", '\0'));
//    printf("ft_strnchr	%s\n", ft_strchr("teste", 'a'));
//	printf("ft_strnchr	%s\n", ft_strchr("teste", 1024));
//	printf("\n\n");
//	printf("strnchr		%s\n", ft_strchr("teste", 't'));
//    printf("strnchr		%s\n", ft_strchr("teste", 'e'));
//    printf("strnchr		%s\n", ft_strchr("teste", '\0'));
//    printf("strnchr		%s\n", ft_strchr("teste", 'a'));
//	printf("strnchr		%s\n", ft_strchr("teste", 1024));
//}