/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:42:44 by root              #+#    #+#             */
/*   Updated: 2025/01/27 18:57:03 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_chartable_linecount(char **table)
{
	size_t	count;

	count = 0;
	while (table[count])
		count++;
	return (count);
}

// Frees a 2D table
void	ft_free_chartable(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

/**
 * @brief Prints all the elements in a table of strings
 * @param char **table of chars
 * @returns 0 on success, 1 on fail
 */
int	ft_print_chartable(char **table)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_chartable_linecount(table);
	while (i < size - 1)
		if (ft_printf("%s\n", table[i++]) == 0)
			return (1);
	return (0);
}
