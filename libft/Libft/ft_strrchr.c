/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:36:04 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:56:34 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	s = s + i;
	if (c == '\0')
		return ((char *) s);
	while (i >= 0)
	{
		if (*s == (char) c)
			return ((char *) s);
		s--;
		i--;
	}
	return (NULL);
}

//int main(void)
//{
//	char s[] = "Hello World this is a TestA";
//	printf("%s\n", ft_strrchr(s, 'A'));
//}