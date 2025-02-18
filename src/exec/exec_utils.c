/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:35:44 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 09:54:54 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	find_cmd(t_mini *mini)
{
	if (!mini->token || !mini->token->next)
		return ;
	mini->token = mini->token->next;
	while (mini->token && mini->token->type != 1)
	{
		if (!mini->token->next)
			break ;
		mini->token = mini->token->next;
	}
}
