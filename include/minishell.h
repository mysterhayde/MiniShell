#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include "../libft/libft.h"

typedef struct s_mini 
{
	int		argc;
	char	**argv;
	char	**envp;
} t_mini;

#endif