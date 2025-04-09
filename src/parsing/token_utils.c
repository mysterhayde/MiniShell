/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:11 by cbopp             #+#    #+#             */
/*   Updated: 2025/04/08 17:41:48 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	free_lastcmd_list

/**
 * @brief Frees a cmd array (array of strings)
 * @param cmd The command array to free
 */
void	free_cmd_arr(char **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}
