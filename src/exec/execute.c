/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:06 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/21 10:50:54 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief expand variables by searching in the env
 * @param char* the variable you want expand
 * @param char** an array with environment variables
 */
static char	*expand(char *str, char **envp)
{
	int		i;
	int		j;
	int		len;
	char	*variable;
	char	*expanded;

	str++;
	i = 0;
	variable = ft_strjoin(str, "=");
	if (!variable)
		return (NULL);
	len = ft_strlen(variable);
	while (ft_strncmp(variable, envp[i], len))
		i++;
	if (!envp[i])
		return (NULL);
	expanded = malloc(sizeof(char) * (ft_strlen(envp[i]) - len + 1));
	if (!expanded)
		return (NULL);
	j = 0;
	while (envp[i][len])
		expanded[j++] = envp[i][len++];
	expanded[j] = '\0';
	return (expanded);
}

char *clear_str(char *str, char **envp)
{
	char *test = expand(str, envp);
	return (test);
}

char	**create_cmd_tab(t_token *token, t_token *backup, char **envp)
{
	int		i;
	int		word;
	char	**tab;

	i = 0;
	word = 0;
	while (token && (token->type == CMD || token->type == ARG))
	{
		word++;
		token = token->next;
	}
	token = backup;
	tab = malloc(sizeof(char *) * (word + 1));
	if (!tab)
		return (NULL);
	while (token && (token->type == CMD || token->type == ARG))
	{
		tab[i] = ft_strdup(clear_str(token->str, envp));
		if (!tab[i++])
			return (NULL);
		token = token->next;
		//TODO : free and delete old nodes
	}
	tab[i] = NULL;
	return (tab);
}

/**
 * @brief Calls of expansion of argument(s) and then manages 
 * 		  builtin or bin commands
 * @param t_mini *mini
 * @details It checks for pipes anywhere in the input because if there's a pipe 
 * 			everything needs to be executed inside a fork. If there's no pipe 
 * 			builtin commands need to be executed without piping.
 */
void	execute(t_mini *mini, char **envp)
{
	char	**cmd;

	cmd = create_cmd_tab(mini->token, mini->backup, envp);
	for(int j = 0; cmd[j]; j++)
		printf("TAB	%s\n", cmd[j]);

	if (!mini->token || !mini->token->str)
		return ;
	if (ft_strmincmp(cmd[0], "exit", 4) == 0)
		exit_builtin(mini, cmd);
	else if (mini->is_pipe)
		mini->ret = minipipe(mini, cmd);
	else if (is_builtin(cmd[0]))
		mini->ret = exec_builtin(mini, cmd);
	else
		mini->ret = exec_bin(mini, cmd);
}
