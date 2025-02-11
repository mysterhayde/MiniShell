/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:04:03 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/11 11:56:33 by cbopp            ###   ########.fr       */
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
	char	*test;

	(void)argc;
	(void)argv;
	init(&mini, envp);
	while (mini.exit == 0)
	{
		ft_printf("%s ", mini.user);
		test = readline("~ MyShell> ");
		parsing(test, &mini);
		execute(&mini);
	}	
 		return (0);
}
