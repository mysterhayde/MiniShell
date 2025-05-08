/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:35:55 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 16:25:41 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Transforms an upper case alphabetical character to lower case.
 * @param c Character to be transformed (if necessary).
 * @return The transformed character.
 */
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c = c + 32;
	return (c);
}

//#include <stdio.h>
//int main(void)
//{
//	printf("%d\n", ft_tolower('z'));
//}