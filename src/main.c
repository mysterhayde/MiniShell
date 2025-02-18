/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:04:03 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 10:13:46 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Sends for all variables that need to be defined
 * @param t_mini *mini
 * @param char **envp
 */
void	init(t_mini *mini, char **envp)
{
	mini->envp = copy_env(envp);
	if (!mini->envp)
	{
		mini->envp = NULL;
		return ;
	}
	setupenv(mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*entry;

	mini.token = NULL;
	mini.backup = NULL;
	(void)argc;
	(void)argv;
	init(&mini, envp);
	while (mini.exit == 0)
	{
		ft_printf("%s ", mini.user);
		entry = readline("~ MyShell> ");
		if (entry == NULL)
			return (0);
		parsing(entry, &mini);
		execute(&mini);
		free_token_list(&mini);
	}
	return (free(mini.user), 0);
}
