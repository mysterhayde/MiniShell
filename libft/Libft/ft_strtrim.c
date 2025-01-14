/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:31:40 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:56:37 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		end;
	int		i;

	i = 0;
	end = 0;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	end = (ft_strlen(s1));
	while (end >= 0 && ft_strchr(set, s1[end]))
		end--;
	str = malloc(sizeof(char) * (end + 2));
	if (str == 0)
		return (NULL);
	while (i <= end)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

//int main(void)
//{
//	char s[] = "ABC123";
//	char c[] = "ABC";
//	printf("%s\n", ft_strtrim(s, c));
//}
