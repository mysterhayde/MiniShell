/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:59:10 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:54:36 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *) s;
	while (n > i)
	{
		ptr[i] = 0;
		i++;
	}
}

// int main(void)
// {
	// char s[] = "Hello World";
	// printf("%s\n", s);
	// ft_bzero(s, 6);
	// printf("%s\n", s);
	// return (0);
// }