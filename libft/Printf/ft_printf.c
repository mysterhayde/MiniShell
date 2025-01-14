/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:08:57 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 11:05:02 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	putchar_pf(char c, int value)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (++value);
}

int	putstr_pf(char *s, int value)
{
	int	i;

	i = 0;
	if (!s)
	{
		value = putstr_pf("(null)", value);
		if (value == -1)
			return (-1);
		return (value);
	}
	while (s[i])
	{
		value = putchar_pf(s[i++], value);
		if (value == -1)
			return (-1);
	}
	return (value);
}

static int	print_pointer_pf(void *p, int value)
{
	unsigned long	un;

	un = (unsigned long) p;
	value = putstr_pf("0x", value);
	if (value == -1)
		return (-1);
	return (write_pointer_pf(un, &value));
}

static int	check_args(const char *format, va_list list, int value, int i)
{
	if (format[i] == 'c')
		value = putchar_pf(va_arg(list, int), value);
	else if (format[i] == 's')
		value = putstr_pf(va_arg(list, char *), value);
	else if (format[i] == 'p')
		value = print_pointer_pf(va_arg(list, void *), value);
	else if (format[i] == 'd' || format[i] == 'i')
		value = putnbr_pf(va_arg(list, int), &value);
	else if (format[i] == 'u')
		value = unsigned_putnbr_pf(va_arg(list, int), &value);
	else if (format[i] == 'x' || format[i] == 'X')
		value = print_hex_pf(va_arg(list, unsigned long), &value, format[i]);
	else if (format[i] == '%')
		value = putchar_pf('%', value);
	return (value);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		return_value;
	int		i;

	i = 0;
	return_value = 0;
	va_start (list, format);
	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			return_value = putchar_pf(format[i++], return_value);
			if (return_value == -1)
				break ;
		}
		else
		{
			return_value = check_args(format, list, return_value, ++i);
			if (return_value == -1)
				break ;
			i++;
		}
	}
	va_end (list);
	return (return_value);
}

//#include <stdio.h>
//
//int main (void)
//{
//	char			c = 'c';
//	char			*s = "Hello World";
//	void			*p = "void test"; 
//	int				i = -746534;
//	int				d = 6344479;
//	unsigned int	u = 42326849;
//	int				x = 2516748;
//	int				X = 1541610;
//
//	printf("\ncustom %d\n", ft_printf(" hello char %c", c));
//	printf("\nprintf %d\n", printf("char %c", c));
//	write (1, "\n", 1);
//	printf("\ncustom %d\n", ft_printf("string %s", s));
//	printf("\nprintf %d\n", printf("string %s", s));
//	write (1, "\n", 1);
//	printf("\ncustom %d\n", ft_printf("char %p", p));
//	printf("\nprintf %d\n", printf("char %p", p));
//	write (1, "\n", 1);
//	printf("\ncustom %d\n", ft_printf("decimal %d", d));
//	printf("\nprintf %d\n", printf("decimal %d", d));
//	write (1, "\n", 1);
//	printf("\ncustom %d\n", ft_printf("integer %i", i));
//	printf("\nprintf %d\n", printf("integer %i", i));
//	write (1, "\n", 1);
//	printf("\ncustom %d\n", ft_printf("unsigned int %u", u));
//	printf("\nprintf %d\n", printf("unsigned int %u", u));
//	write (1, "\n", 1);
//	printf("\ncustom %d\n", ft_printf("char %x", x));
//	printf("\nprintf %d\n", printf("char %x", x));
//	write (1, "\n", 1);
//	printf("\ncustom %d\n", ft_printf("char %X", X));
//	printf("\nprintf %d\n", printf("char %X", X));
//	write (1, "\n", 1);
//	printf("\ncustom %d\n", ft_printf("pourcent %%"));
//	printf("\nprintf %d\n", printf("pourcent %%"));
//}