/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:38:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:42 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_min_int(void)
{
	char	*str;

	str = malloc(12 * sizeof(char));
	if (str == 0)
		return (NULL);
	ft_strlcpy(str, "-2147483648", 12);
	return (str);
}

/**
 * @brief Checks if an integer is negative
 * @returns 1 if true, 0 if false
 */
int	ft_is_negative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static char	*ft_convert(int n, int len, char *str, int negative)
{
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = (n % 10) + '0';
		len --;
		n /= 10;
	}
	if (negative == 1)
		str[0] = '-';
	return (str);
}

/**
 * @brief Converts an integer in to a string
 * @param n The integer to convert
 * @return A pointer to the first character in the string.
 */
char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		div;
	int		negative;

	div = 1;
	len = 1;
	negative = 0;
	if (n == -2147483648)
		return (ft_min_int());
	if (ft_is_negative(n))
	{
		n = -n;
		negative = 1;
	}
	while (n / div > 9)
	{
		len++;
		div *= 10;
	}
	str = malloc((len + 1 + negative) * sizeof(char));
	if (str == 0)
		return (NULL);
	return (ft_convert(n, len + negative, str, negative));
}

//int main(void)
//{
//	int nb = 9874;  
//	printf("Final %s\n", ft_itoa(nb));
//}