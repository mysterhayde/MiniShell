/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:47:30 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:57:50 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Compares the first n bytes (each interpreted as unsigned char) of the
 * memory areas s1 and s2.
 * @param s1 A pointer to the first string.
 * @param s2 A pointer to the second string.
 * @param n The maximum number of bytes to compare.
 * @return an integer less than, equal to, or greater than zero if the first n
 * bytes of s1 is found, respectively, to be less than, to match, or be greater
 * than the first n bytes of s2.
 */
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