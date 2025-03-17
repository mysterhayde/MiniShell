/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_null.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:25:22 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/17 15:55:30 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Shifts elements in cmd array to fill empty spots
 * @param cmd The command array
 * @param i Starting index for shifting
 * @return Last index that was modified
 */
int	shift_cmd_elements(char **cmd, int i)
{
	int	j;

	free(cmd[i]);
	j = i;
	while (cmd[j + 1])
	{
		cmd[j] = cmd[j + 1];
		j++;
	}
	cmd[j] = NULL;
	return (j);
}

/**
 * @brief Removes any empty arguements/commands in the command list
 * @param cmd_token The token holding the command and all the arguments
 */
void	fix_index(t_token *cmd_token)
{
	int		i;
	char	**cmd;
	int		all_empty;

	if (!cmd_token || !cmd_token->cmd)
		return ;
	cmd = cmd_token->cmd;
	i = 0;
	all_empty = 1;
	while (cmd[i])
	{
		if (cmd[i][0] != '\0')
			all_empty = 0;
		if (cmd[i][0] == '\0')
		{
			shift_cmd_elements(cmd, i);
			i--;
		}
		i++;
	}
	if (all_empty && !cmd[0])
		cmd[0] = ft_strdup("");
}
