#include "../../include/minishell.h"

/**
 * @brief Calls of expansion of arguement and then manages builtin or bin commands
 * @param t_mini *mini
 */
void	execute(t_mini *mini)
{
	char	**cmd;
	int		i;

	//Make cmd table
	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = expand(cmd[i]);
		i++;
	}
	//Need to add ispipe check below
	if (cmd && ft_strmincmp(cmd[0], "exit", 4) == 0)
		exit_builtin(mini);
	else if (cmd && is_builtin(cmd[0]))
		mini->ret = exec_builtin(mini, cmd);
}
