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

typedef struct s_children
{
	pid_t	pid;
	t_children	*next;
}	t_children;

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef struct s_token
{
	char			*token;
	t_bool			cmd;
	t_bool			arg;
	struct s_token	*next;
}	t_token;

typedef struct s_mini 
{
	char		**envp;
	char		*user;
	char		*cur_path;
	t_token		*tokens;
	int			exit;
	int			ret;
	t_children	children;
} t_mini;

// Init
void	getcurpath(t_mini *mini);
void	setupenv(t_mini *mini);

// Cmds
int		pwd(t_mini *mini);
int		cd(const char *path);
int		env(t_mini *mini);
int		echo(char **cmd);
void	exit_builtin(int n);

// Exec
void	execute(t_mini *mini);
int		is_builtin(char *cmd);
int		exec_builtin(t_mini *mini, char **cmd);

#endif