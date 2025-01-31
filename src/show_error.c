/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:20:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/31 17:54:39 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	show_error(char *str)
{
	ft_putendl_fd(COLOR_RED"Error", 2);
	perror(str);
	ft_putendl_fd(COLOR_RESET, 2);
}
