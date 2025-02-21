/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:25:33 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/21 11:07:29 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief transforms a string into an long
 */
long	ft_atol(const char *str)
{
	int		i;
	int		is_neg;
	long	total;

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
