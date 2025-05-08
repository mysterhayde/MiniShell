/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:31:14 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:44:24 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if c is ascii
 * @param c The character to check
 * @returns 1 if true, 0 if false
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
