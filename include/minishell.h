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
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_mini 
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*user;
	char	**path;
} t_mini;

// Init
int	setupenv(t_mini mini);

#endif