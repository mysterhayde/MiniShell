/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:47 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/27 22:51:13 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Gets current working directory
 * @details Uses getcurpath(t_mini *mini) to update mini->cur_path
 * @returns 0 on success, 1 on failure
 */
int	pwd(void)
{
	int		len;
	char	*buf;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	getcwd(buf, BUFFER_SIZE);
	if (buf != NULL)
	{
		len = ft_strlen(buf);
		write(STDOUT_FILENO, buf, len);
		write(STDOUT_FILENO, "\n", 1);
		free(buf);
		return (0);
	}
	perror("pwd");
	return (1);
}
