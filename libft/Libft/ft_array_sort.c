/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:33:30 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/08 09:49:39 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Use a selection sort algorithm to sort an array of strings in
 * ascending order.
 * @param tab The array of strings to sort
 * @return The same array of strings, sorted in ascending order
 */
char	**ft_asort_char(char **tab)
{
	int		j;
	int		i;
	int		pos;
	char	*temp;
	char	*min_str;

	i = -1;
	while (tab[++i])
	{
		j = i;
		pos = i;
		min_str = tab[i];
		while (tab[++j])
		{
			if (ft_strcmp(tab[j], min_str) < 0)
			{
				min_str = tab[j];
				pos = j;
			}
		}
		temp = tab[i];
		tab[i] = tab[pos];
		tab[pos] = temp;
	}
	return (tab);
}
