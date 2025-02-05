/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:10:09 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/05 18:07:41 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_children
{
	pid_t				pid;
	int					wstatus;
	struct t_children	*next;
}	t_children;

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
}	t_token;

typedef struct s_mini 
{
	char		**envp;
	char		*user;
	char		*cur_path;
	t_bool		is_pipe;
	size_t		pipenum;
	t_token		*token;
	t_token		*backup;
	int			exit;
	int			ret;
	t_children	*children;
	t_debug	*debug;
}	t_mini;

/*----------------------------------- Init -----------------------------------*/
void	getcurpath(t_mini *mini);
void	setupenv(t_mini *mini);

/*----------------------------------- Cmds -----------------------------------*/
int		pwd(t_mini *mini);
int		cd(const char *path);
int		env(t_mini *mini);
int		echo(char **cmd);
void	exit_builtin(t_mini *mini);

/*--------------------------------- Execute ---------------------------------*/
void	execute(t_mini *mini);
int		is_builtin(char *cmd);
int		exec_builtin(t_mini *mini, char **cmd);
int		exec_bin(t_mini *mini, char **cmd);
int		minipipe(t_mini *mini);
void	try_pipe(int	*pipefd);

/*---------------------------------- Path -----------------------------------*/
char	*find_path(char *cmd, char **envp);

/*--------------------------------- Parsing ---------------------------------*/

int		is_operator(t_mini *mini, char *str);
void	parsing(char *str, t_mini *mini);
char	**split_args(char *str);

/*---------------------------------- Error ----------------------------------*/

void	show_error(char *str);

#endif