/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:35:44 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/31 11:13:39 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	find_cmd(t_mini *mini)
{
	if (!mini->token || !mini->token->next)
		return ;
	mini->token = mini->token->next;
	while (mini->token && mini->token->type != CMD)
	{
		if (!mini->token->next)
			break ;
		mini->token = mini->token->next;
	}
}
