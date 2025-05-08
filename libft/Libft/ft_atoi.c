/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:15:02 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:40:10 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief transforms a string into an integer
 * @param str Pointer to a const str
 * @returns The integer transfromed from ascii
 */
int	ft_atoi(const char *str)
{
	int	i;
	int	is_neg;
	int	total;

	i = 0;
	is_neg = 0;
	total = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
	{
		if ((str[i] != '+' && str[i] != '-') && (str[i] < '0' && str[i] > '9'))
			return (0);
		i++;
	}
	if (str[i] == '-')
		is_neg = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = total * 10 + (str[i] - 48);
		i++;
	}
	if (is_neg == 1)
		total = -total;
	return (total);
}

//int main(void)
//{
//	char n[40] = "\t\v\f\r\n \f-06050-1234";
//	int i1 = printf("%d\n",atoi(n));
//	int i2 = printf("%d\n", ft_atoi(n));
//
//	// if (i1 == i2)
//	// 	exit(TEST_SUCCESS);
//	// exit(TEST_KO);
//}
