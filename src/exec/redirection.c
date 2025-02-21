/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:34:38 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/21 16:14:26 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	here_doc(int fd, char *limiter)
{
	char	*line;

	while(1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return ;
		if (!ft_strncmp(limiter, line, ft_strlen(line) - 1))
			break;
		ft_putstr_fd(line, fd);
	}
}