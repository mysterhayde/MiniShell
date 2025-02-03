/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:54:12 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/03 17:00:26 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_operator(char *str)
{
	if (ft_strmincmp(str, "|", 1) == 0)
		return (1);
	// else if (ft_strmincmp(str, "", 2))
	// 	return (1);
	// else if (ft_strmincmp(str, "(", 1))
	// 	return (1);
	// else if (ft_strmincmp(str, ")", 1))
	// 	return (1);
	// else if (ft_strmincmp(str, "<", 1))
	// 	return (1);
	// else if (ft_strmincmp(str, ">", 1))
	// 	return (1);
	// else if (ft_strmincmp(str, "&", 1))
	//	return (1);
	return (0);
}
