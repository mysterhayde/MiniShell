/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:20:31 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/28 14:46:10 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Gets USER from env
 * @param t_mini *mini
 */
static void	getuser(t_mini *mini)
{
	int		i;

	i = 0;
	if (mini->user)
		free(mini->user);
	if (!mini->envp)
		mini->user = ft_strdup(COLOR_BLUE"user"COLOR_RESET);
	while (mini->envp[i])
	{
		if (ft_strnstr(mini->envp[i], "USER=", 5))
		{
			mini->user = ft_strjoin(COLOR_BLUE, mini->envp[i] + 5);
			return ;
		}
		i++;
	}
	mini->user = ft_strdup(COLOR_BLUE"user"COLOR_RESET);
}

char	*get_prompt(t_mini *mini)
{
	char	*prompt;

	getuser(mini);
	prompt = ft_strjoin(mini->user, COLOR_PURPLE" ~ MyShell> "COLOR_RESET);
	if (!prompt)
		return (NULL);
	return (prompt);
}
