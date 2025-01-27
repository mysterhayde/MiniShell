# include "../../include/minishell.h"

/**
 * @brief Gets current working directory
 * @warning Returns 0 on success, 1 on failure
 */
int	pwd(void)
{
	char	buf[BUFFER_SIZE];
	char	*tmp;

	tmp = malloc(sizeof(char *) * BUFFER_SIZE);
	tmp = getcwd(buf, BUFFER_SIZE);
	if (tmp != NULL)
	{
		ft_printf("%s\n", buf);
		return (0);
	}
	return (1);
}