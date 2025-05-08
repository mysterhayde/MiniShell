/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:56:16 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 16:08:41 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Writes a character to a given fd.
 * @param c The character to print.
 * @param fd The fd to write to.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

//int main(void)
//{
//	int i = 0;
//	char s[] = "Hello Wolrd";
//	while (s[i])
//	{
//		ft_putchar_fd(s[i], 1);
//		i++;
//	}
//}