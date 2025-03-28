/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:54 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/28 14:33:19 by hdougoud         ###   ########.fr       */
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

static char	**make_env(void)
{
	char	**env;

	env = malloc(sizeof(char *) * 3);
	if (!env)
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin");
	env[1] = ft_strdup("USER=user");
	env[2] = NULL;
	return (env);
}

void	setupenv(t_mini *mini, char **envp)
{
	if (!envp || !*envp)
		mini->envp = make_env();
	else
		mini->envp = copy_env(envp);
	//getuser(mini);
	getcurpath(mini);
}
