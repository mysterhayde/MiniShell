#include "../../include/minishell.h"

int	exec_bin(t_mini *mini, char **cmd)
{
	pid_t	pid;
	char	*path;
	int		ret;
	int		i;

	pid = fork();
	if (pid == -1)
		perror("PID: ");
	if (pid == 0)
	{
		path = find_path(cmd[0], mini->envp);
		if (!path)
		{
			// free_cmd(cmd);
			perror("!path: ");
		}
		if (execve(path, cmd, mini->envp) == -1)
		{
			free(path);
			// free_cmd(cmd);
			perror("execve: ");
			return (1);
		}
	}
}
