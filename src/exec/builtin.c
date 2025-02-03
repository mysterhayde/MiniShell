#include "../../include/minishell.h"

/**
 * @brief Manages builtin command execution
 * @param t_mini *mini
 * @param char *cmd
 * @returns Result of command executed
 */
int	exec_builtin(t_mini *mini, char **cmd)
{
	int	ret;

	ret = 0;
	if (ft_strmincmp(cmd[0], "pwd", 3) == 0)
		ret = pwd(mini);
	else if (ft_strmincmp(cmd[0], "export", 6) == 0)
		return (1);
	else if (ft_strmincmp(cmd[0], "cd", 2) == 0)
		ret = cd(cmd);
	else if (ft_strmincmp(cmd[0], "env", 3) == 0)
		return (1);
	else if (ft_strmincmp(cmd[0], "echo", 4) == 0)
		ret = echo(cmd);
	else if (ft_strmincmp(cmd[0], "unset", 5) == 0)
		return (1);
	return (ret);
}

/**
 * @brief Check if a command is a builtin or not
 * @param char *cmd
 * @returns 1 if builtin, 0 if /bin
 */
int	is_builtin(char *cmd)
{
	if (ft_strmincmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strmincmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strmincmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strmincmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strmincmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strmincmp(cmd, "unset", 5) == 0)
		return (1);
	return (0);
}
