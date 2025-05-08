/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:57:12 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:44:42 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if c is an ascii digit
 * @param c The character to check
 * @returns 1 if true, 0 if false
 */
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
