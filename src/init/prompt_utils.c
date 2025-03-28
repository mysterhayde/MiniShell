/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:20:31 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/25 16:15:23 by cbopp            ###   ########.fr       */
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
