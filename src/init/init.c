/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:54 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/05 15:03:55 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	getcurpath(t_mini *mini)
{
	char	buf[BUFFER_SIZE];

	mini->cur_path = getcwd(buf, BUFFER_SIZE);
	if (mini->cur_path != NULL)
		return ;
	perror("Pwd");
}

/**
 * @brief Gets USER from env
 * @param t_mini *mini
 */
static void	getuser(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->envp[i] && ft_strnstr(mini->envp[i], "USER=", 5) == 0)
	{
		i++;
	}
	mini->user = ft_strdup(mini->envp[i] + 5);
}

void	setupenv(t_mini *mini)
{
	getuser(mini);
	getcurpath(mini);
}
