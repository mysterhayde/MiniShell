#include "../../include/minishell.h"

// pid_t	go_fork(void)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		//free()
// 	return (pid);
// }

// int	minipipe(t_mini *mini, char **cmd)
// {
// 	int		fd[2];
// 	int		i;

// 	i = 0;
// 	while (i < pipenum + 1)
// 		mini->children = mini->children->next;
// 	if builtin 
// 		mini->children->pid = go_fork(); 
// 		exec_builtin()
// 	else
// 		exec_bin()

// }

/**
 * @brief Calls of expansion of argument(s) and then manages builtin or bin commands
 * @param t_mini *mini
 * @details It checks for pipes anywhere in the input because if there's a pipe 
 * 			everything needs to be executed inside a fork. If there's no pipe 
 * 			builtin commands need to be executed without piping.
 */
void	execute(t_mini *mini)
{
	// int		i;

	// cmd = cmd_tab(mini);
	// i = 1;
	// while (cmd && cmd[i])
	// {
	// 	cmd[i] = expand(cmd[i]);
	// 	i++;
	// }
	//Need to add ispipe check below
	if (mini->token->cmd && ft_strmincmp(mini->token->cmd[0], "exit", 4) == 0)
		exit_builtin(mini);
	// else if (mini->token->str && mini->is_pipe)
	// 	mini->ret = minipipe(mini, cmd);
	else if (mini->token->cmd && is_builtin(mini->token->cmd) && !mini->is_pipe)
		mini->ret = exec_builtin(mini, mini->token->cmd);
	else if (mini->token->cmd)
	{
		// mini->children->pid = go_fork();
		mini->ret = exec_bin(mini, mini->token->cmd);
	}
}
