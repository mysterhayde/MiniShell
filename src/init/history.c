/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:45:11 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 10:57:01 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_readline_history(void)
{
	rl_bind_key('\t', rl_complete);
	using_history();
}

void	add_to_history(const char *command)
{
	if (command && *command && command[0] != ' ')
		add_history(command);
}

void	cleanup_history(void)
{
	clear_history();
	rl_clear_history();
}
