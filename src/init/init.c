/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:54 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/24 23:37:05 by cbopp            ###   ########.fr       */
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

/**
 * @brief Gets USER from env
 * @param t_mini *mini
 */
static void	getuser(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->envp[i] && ft_strnstr(mini->envp[i], "USER=", 5) == 0)
	{
		i++;
	}
	mini->user = ft_strjoin(COLOR_BLUE, mini->envp[i] + 5);
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
	getuser(mini);
	getcurpath(mini);
}
