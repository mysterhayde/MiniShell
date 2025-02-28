/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:41:56 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/28 13:02:06 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief compares s1 and s2 strings
 * @return 1 if there is a difference and 0 if the 2 strings are identical
 * @warning only works with strings ending in null
 */
int	strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (1);
	}
	if ((!s1[i] && s2[i]) || s1[i] && !s2[i])
		return (1);
	if (!s1[i] && !s2[i])
		return (0);
}
