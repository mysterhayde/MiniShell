/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:20:31 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 18:27:48 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_prompt(t_mini *mini)
{
	char	*temp;
	char	*prompt;

	temp = ft_strjoin(mini->user, " ~ MyShell> ");
	if (!temp)
		return (NULL);
	prompt = ft_strdup(temp);
	if (!prompt)
		return(free(prompt), NULL);
	free(temp);
	return (prompt);
}
