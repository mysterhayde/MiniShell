/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:54:33 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/20 16:39:03 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief compares s1 with s2 on n characters
 * @return returns 0 if the 2 strings are identical, otherwise
 * returns the deifference of the 2 strings
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*us1;
	unsigned char	*us2;

	i = 0;
	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	while (n > i)
	{
		if (us1[i] == '\0' && us2[i] == '\0')
			return (0);
		if (us1[i] != us2[i] || us1[i] == '\0' || us2[i] == '\0')
			return (us1[i] - us2[i]);
		i++;
	}
	return (0);
}

int	ft_strmincmp(const char *s1, const char *s2, size_t min)
{
	unsigned int	i;
	unsigned char	*us1;
	unsigned char	*us2;
	size_t			size;

	i = 0;
	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	size = ft_strlen(s1);
	if (size < min)
		size = min;
	while (size > i)
	{
		if (us1[i] == '\0' && us2[i] == '\0')
			return (0);
		if (us1[i] != us2[i] || us1[i] == '\0' || us2[i] == '\0')
			return (us1[i] - us2[i]);
		i++;
	}
	return (0);
}

//int main(void)
//{
//	char s1[] = "test1";
//	char s2[] = "tester";
//	printf("%d\n", ft_strncmp(s1, s2, 20));
//	printf("%d\n", strncmp(s1, s2, 20));
//	return (0);
//}