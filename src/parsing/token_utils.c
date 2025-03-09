/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:11 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/09 14:18:18 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
