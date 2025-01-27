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
	char	**envp;
	char	*user;
	char	*cur_path;
} t_mini;

// Init
void	getcurpath(t_mini *mini);
void	setupenv(t_mini *mini);

// cmds
int		pwd(t_mini *mini);
int		cd(char *path);

#endif