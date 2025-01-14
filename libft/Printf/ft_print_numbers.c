/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:08:50 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:54:50 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	putnbr_pf(int nb, int *value)
{
	if (nb == -2147483648)
	{
		(*value) = putstr_pf("-2147483648", (*value));
		if ((*value) == -1)
			return (-1);
		return ((*value));
	}
	if (nb < 0)
	{
		nb = -nb;
		(*value) = putchar_pf('-', (*value));
		if ((*value) == -1)
			return (-1);
	}
	if (nb > 9)
	{
		if (putnbr_pf(nb / 10, value) == -1)
			return (-1);
	}
	(*value) = putchar_pf(nb % 10 + '0', (*value));
	if ((*value) == -1)
		return (-1);
	return ((*value));
}

int	unsigned_putnbr_pf(unsigned int nb, int *value)
{
	if (nb > 9)
	{
		if (unsigned_putnbr_pf(nb / 10, value) == -1)
			return (-1);
	}
	(*value) = putchar_pf(nb % 10 + '0', (*value));
	if (*value == -1)
		return (-1);
	return ((*value));
}

int	print_hex_pf(unsigned int un, int *value, char param)
{
	int				mod;
	const char		*dict1;
	const char		*dict2;

	dict1 = "0123456789abcdef";
	dict2 = "0123456789ABCDEF";
	if (un >= 16)
	{
		if (print_hex_pf(un / 16, value, param) == -1)
			return (-1);
	}
	mod = un % 16;
	if (param == 'x')
	{
		(*value) = putchar_pf(dict1[mod], (*value));
		if ((*value) == -1)
			return (-1);
	}
	else
	{
		(*value) = putchar_pf(dict2[mod], (*value));
		if ((*value) == -1)
			return (-1);
	}
	return (*value);
}

int	write_pointer_pf(unsigned long un, int *value)
{
	int				mod;
	const char		*dict;

	dict = "0123456789abcdef";
	if (un >= 16)
		write_pointer_pf(un / 16, value);
	mod = un % 16;
	(*value) = putchar_pf(dict[mod], (*value));
	if ((*value) == -1)
		return (-1);
	return ((*value));
}
