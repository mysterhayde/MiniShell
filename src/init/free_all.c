/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:18:45 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/09 14:20:09 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_all(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->user)
		free(mini->user);
	if (mini->token || mini->backup)
		free_token_list(mini);
	if (mini->envp)
		free_env_arr(mini->envp);
}
