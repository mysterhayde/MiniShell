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
 * @enum C_OP = 3
 * @enum R_OP = 4
 */
typedef enum e_type
{
	CMD = 1,
	ARG = 2,
	C_OP = 3,
	R_OP = 4
}	t_type;

typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_mini 
{
	char	**envp;
	char	*user;
	char	*cur_path;
	t_token	*tokens;
} t_mini;

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

char	*parsing(char *str, t_token *token);


/*---------------------------------- Error ----------------------------------*/

void	show_error(char *str);

#endif