/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:47:30 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:55:34 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	unsigned int	i;

	i = 0;
	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	while (n > i)
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}

//int main(void)
//{
//	char s1[] = "atome";
//	char s2[] = "atomeu";
//	printf("%d\n", ft_memcmp(s1, s2, 8));
//	printf("%d\n", memcmp(s1, s2, 8));
//	return (0);
//}