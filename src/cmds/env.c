/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:39 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/05 15:03:40 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief prints all the environment variables
 * @returns 0 on success, 1 on fail
 */
int	env(t_mini *mini)
{
	if (ft_print_chartable(mini->envp) == 0)
		return (0);
	return (1);
}
