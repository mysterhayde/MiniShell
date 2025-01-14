/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:45:42 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:56:14 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

//int main(void)
//{
//	char s[] = "Hello World";
//	ft_striteri(s, &ft_test);
//}
//
//oid ft_test(unsigned int n, char *c)
//{
//	if (*c >= 97 && *c <= 122 && n < 8)
//		*c -=32;
//}