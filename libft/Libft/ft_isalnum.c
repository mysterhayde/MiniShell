/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:09:07 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/03 11:41:01 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Check if the character is alphanumeric.
 * @return 1 if the character is alphanumeric, 0 otherwise.
 * @details The ft_isalnum() function tests is the character c is
 * 			alphabetic or digit (alphanumeric).
 */
int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122))
		return (1);
	return (0);
}
