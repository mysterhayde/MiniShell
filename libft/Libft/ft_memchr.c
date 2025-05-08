/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:31:01 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:56:05 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Searches for the character 'c' in the first 'n' bytes of string 's'
 * @param s A pointer to the byte of the string.
 * @param c The character that is being looked for.
 * @param n The maximum number of bytes to look in.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*us;
	unsigned char	uc;

	us = (unsigned char *) s;
	uc = (unsigned char) c;
	while (n > 0)
	{
		if (*us == uc)
			return (us);
		us++;
		n--;
	}
	return (NULL);
}

//int main(void)
//{
//	char s[] = "hello World";
//	printf("%s\n", ft_memchr(s, 'W', 11));
//	return (0);
//}