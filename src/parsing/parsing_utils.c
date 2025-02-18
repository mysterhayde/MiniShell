/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:24:41 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/18 17:55:49 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_operator(t_mini *mini, char *str)
{
	if (ft_strmincmp(str, "|", 1) == 0)
	{
		mini->is_pipe = TRUE;
		mini->pipe_num++;
		return (PIPE);
	}
	else if (ft_strmincmp(str, "<", 1) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, ">", 1) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, ">>", 2) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, "<<", 2) == 0)
		return (HERE_DOC);
	return (0);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

int	is_printable(char c)
{
	if (c == '!' || c == '$' || c == '\"' || c == '\'')
		return (1);
	else
		return (0);
}
