/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:06 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/21 16:39:03 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief expand variables by searching in the env
 * @param str the variable you want expand
 * @param envp an array with environment variables
 * @details give a string containing only the variable to be expanded
 */
static char	*expand(char *str, char **envp)
{
	int		i;
	int		j;
	int		len;
	char	*variable;
	char	*expanded;

	i = 0;
	j = 0;
	variable = ft_strjoin(str + 1, "=");

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
	while (envp[i][len])
		expanded[j++] = envp[i][len++];
	expanded[j] = '\0';
	return (free(variable), expanded);
}
/**
 * @brief remove quotation marks if necessary and expand variables
 */
char *clear_str(char *str, char **envp)
{
	char	*test;
	
	if (str[0] == '$')
		return (test = expand(str, envp));
	return (str);
}

char	**create_cmd_tab(t_token **token, t_token *backup, char **envp)
{
	int		i;
	int		word;
	char	**tab;

	i = 0;
	word = 0;
	while (*token && ((*token)->type == CMD || (*token)->type == ARG))
	{
		word++;
		*token = (*token)->next;
	}
	*token = backup;
	tab = malloc(sizeof(char *) * (word + 1));
	if (!tab)
		return (NULL);
	while (*token && ((*token)->type == CMD || (*token)->type == ARG))
	{
		tab[i] = (clear_str((*token)->str, envp));
		if (!tab[i++])
			return (NULL);
		*token = (*token)->next;
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
	
	if (!mini->token || !mini->token->str)
		return ;
	cmd = create_cmd_tab(&mini->token, mini->backup, envp);
	for(int j = 0; cmd[j]; j++)									//debug
		printf("TAB	%s\n", cmd[j]);								//debug

	if (mini->token)											//debug
		if (mini->token->type == HERE_DOC)						//debug
			here_doc(STDOUT_FILENO, mini->token->next->str);	//debug


	if (ft_strmincmp(cmd[0], "exit", 4) == 0)
		exit_builtin(mini, cmd);
	else if (mini->is_pipe)
		mini->ret = minipipe(mini, cmd);
	else if (is_builtin(cmd[0]))
		mini->ret = exec_builtin(mini, cmd);
	else
		mini->ret = exec_bin(mini, cmd);
}
