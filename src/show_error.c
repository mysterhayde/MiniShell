/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:20:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/21 08:14:10 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_err_prefix(void)
{
	write(STDERR_FILENO, "minishell: ", 11);
}

void	show_err_msg(char *cmd, char *error)
{
	print_err_prefix();
	if (cmd)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	if (error)
		write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, "\n", 1);
}

void	show_error_exit(char *cmd, char *error, int code)
{
	show_err_msg(cmd, error);
	exit(code);
}

int	show_err_return(char *cmd, char *err, int code)
{
	show_err_msg(cmd, err);
	return (code);
}

void	show_cmd_not_found(char *cmd)
{
	show_err_msg(cmd, "command not found");
}
