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
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

/**
 * @brief Type of token
 * @enum CMD = 1
 * @enum ARG = 2
 * @enum PIPE = 3
 * @enum RDIT = 4
 * @enum FILE = 5
 */
typedef enum e_type
{
	CMD = 1,
	ARG = 2,
	PIPE = 3,
	RDIT = 4,	//Redirections
	FD = 5
}	t_type;

typedef struct s_debug
{
	char			**cmd;
	struct s_debug	*next;
}	t_debug;


typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token	*next;
//	struct s_token	*last;
}	t_token;

typedef struct s_mini 
{
	char	**envp;
	char	*user;
	char	*cur_path;
	t_bool	is_pipe;
	t_token	*token;
	t_token	*backup;
	t_debug	*debug;
}	t_mini;

// Init
void	getcurpath(t_mini *mini);
void	setupenv(t_mini *mini);

// cmds
int		pwd(t_mini *mini);
int		cd(const char *path);
int		env(t_mini *mini);
int		echo(t_bool newline, char *str);
void	exit_builtin(int n);


/*--------------------------------- Parsing ---------------------------------*/

int		is_operator(t_mini *mini, char *str);
void	parsing(char *str, t_mini *mini);
char	**split_args(char *str);

/*---------------------------------- Error ----------------------------------*/

void	show_error(char *str);

#endif