/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:43:54 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 16:10:27 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Writes a string to a given fd.
 * @param s A pointer to the string to write.
 * @param fd The fd to write to.
 */
void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
}

//int main(void)
//{
//	char s[] = "Hello World";
//	ft_putstr_fd(s, 1);
//}