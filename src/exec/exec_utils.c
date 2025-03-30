/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:35:44 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/30 22:46:47 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	file_access_failed(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

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
