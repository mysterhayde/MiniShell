/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:20:31 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/19 14:53:30 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_prompt(t_mini *mini)
{
	char	*prompt;

	prompt = ft_strjoin(mini->user, COLOR_PURPLE" ~ MyShell> "COLOR_RESET);
	if (!prompt)
		return (NULL);
	return (prompt);
}
