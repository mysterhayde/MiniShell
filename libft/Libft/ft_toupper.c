/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:24:59 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 16:25:54 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Transforms an lower case alphabetical character to upper case.
 * @param c Character to be transformed (if necessary).
 * @return The transformed character.
 */
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c = c - 32;
	return (c);
}

//int main(void)
//{
//	printf("%d\n", ft_toupper('g'));
//}