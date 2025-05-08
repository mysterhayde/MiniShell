/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:31:40 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 16:24:31 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Trims the start and end of a string of characters 'set'.
 * @param s1 A pointer to the string to be trimmed.
 * @param set The set of characters to trim from 's1'.
 * @return The trimmed string.
 */
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

void	ft_strtrim_nc(char **s1, char const *set)
{
	char	*str;
	int		end;

	end = 0;
	str = *s1;
	while (*str && ft_strchr(set, *str))
		str++;
	*s1 = str;
	end = (ft_strlen(str) - 1);
	while (end >= 0 && ft_strchr(set, str[end]))
		end--;
	if (end >= 0)
		(str[end + 1]) = '\0';
}
//int main(void)
//{
//	char s[] = "ABC123";
//	char c[] = "ABC";
//	printf("%s\n", ft_strtrim(s, c));
//}
