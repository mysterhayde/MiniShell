#include "../../include/minishell.h"

/**
 * @brief Gets current working directory
 * @details Uses getcurpath(t_mini *mini) to update mini->cur_path
 * @returns 0 on success, 1 on failure
 */
int	pwd(t_mini *mini)
{
	getcurpath(mini);
	if (mini->cur_path != NULL)
	{
		ft_printf("%s\n", mini->cur_path);
		return (0);
	}
	perror("pwd");
	return (1);
}
