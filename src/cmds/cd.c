#include "../../include/minishell.h"

/**
 * @brief Basic cd, not completed
 * @param constchar *path
 * @returns 0 on success, 1 on fail
 * @warning DOES NOT WORK WITH ABSOLUTE PATH
 */
int	cd(const char *path)
{
	if (chdir(path) == 0)
		return (0);
	perror("cd");
	(void)path;
	return (1);
}
