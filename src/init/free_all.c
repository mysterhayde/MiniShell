/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:18:45 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/26 16:56:42 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_all(t_mini *mini)
{
	if (mini->user)
		free(mini->user);
	if (mini->cur_path)
		free(mini->cur_path);
	if (mini->token || mini->backup)
		free_token_list(mini);
}
