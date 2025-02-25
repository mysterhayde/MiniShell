/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:30:43 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/25 16:05:44 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	history_builtin(char **args)
{
	HIST_ENTRY	**hist_list;
	int			i;

	if (!args[1])
	{
		hist_list = history_list();
	}
	
}
