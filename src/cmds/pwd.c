/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:47 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/05 15:03:48 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Gets current working directory
 * @details Uses getcurpath(t_mini *mini) to update mini->cur_path
 * @returns 0 on success, 1 on failure
 */
int	pwd(t_mini *mini)
{
	getcurpath(mini);
	if (mini->cur_path != NULL)
	{
		ft_printf("%s\n", mini->cur_path);
		return (0);
	}
	perror("pwd");
	return (1);
}
