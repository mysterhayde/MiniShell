/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:10:09 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 18:23:46 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/*---------------------------------- ENUM ------------------------------------*/

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

/**
 * @brief Type of token
 * @enum CMD 		= 1
 * @enum ARG 		= 2
 * @enum PIPE 		= 3
 * @enum RDIT 		= 4
 * @enum FILE 		= 5
 * @enum HERE_DOC	= 6
 * @enum LIMITER	= 7
 */
typedef enum e_type
{
	CMD			= 1,
	ARG			= 2,
	PIPE		= 3,
	RDIT		= 4, // Redirection
	FILES		= 5,
	HERE_DOC	= 6,
	LIMITER		= 7
}	t_type;

/*------------------------------- STRUCTURES ---------------------------------*/

typedef struct s_pipe
{
	int		*pipe_fds;
	pid_t	*pids;
}	t_pipe;

typedef struct s_token
{
	char			**cmd;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_mini
{
	char		**envp;
	char		*user;
	char		*cur_path;
	int			pipe_num;
	t_bool		is_pipe;
	t_token		*token;
	t_token		*backup;
	int			exit;
	int			ret;
}	t_mini;

extern int	g_signo;

/*---------------------------------- INIT ------------------------------------*/

void	getcurpath(t_mini *mini);
void	setupenv(t_mini *mini);
void	init_readline_history(void);
void	add_to_history(const char *command);
void	cleanup_history(void);
int		setup_signal_handlers(void);
void	reset_signals_for_child(void);
int		check_signal_interrupt(void);
char	*get_prompt(t_mini *mini);

/*--------------------------------- Builtins --------------------------------*/

int		pwd(t_mini *mini);
int		cd(const char *path);
int		env(t_mini *mini);
int		match_var_name(const char *env_var, const char *var_name);
int		export(t_mini *mini, char **cmd);
char	**copy_env(char **env);
size_t	get_env_size(char **env);
t_bool	is_valid_identifier(char *str);
int		echo(char **cmd);
int		unset(t_mini *mini, char **cmd);
int		exit_builtin(t_mini *mini, char **cmd);

/*--------------------------------- Execute ---------------------------------*/
void	execute(t_mini *mini);
int		is_builtin(char *cmd);
int		exec_builtin(t_mini *mini, char **cmd);
int		exec_bin(t_mini *mini, char **cmd);
int		minipipe(t_mini *mini);
void	find_cmd(t_mini *mini);
int		exec_pipe_cmd(t_mini *mini, int i, int *pipe_fds);
int		wait_pipe_children(t_mini *mini, t_pipe *p);
int		run_pipe_commands(t_mini *mini, t_pipe *p);
void	close_all_pipes(int pipe_count, int *pipe_fds);
int		create_pipes(int pipe_count, int **pipe_fds);
int		wait_for_children(t_mini *mini, pid_t *pids);

/*---------------------------------- Path -----------------------------------*/
char	*find_path(char *cmd, char **envp);

/*--------------------------------- Parsing ---------------------------------*/

int		is_separator(char c);
int		is_operator(t_mini *mini, char *str);

char	**split_args(char *str);
char	**check_bash_syntax(char **split);

void	free_token_list(t_mini *mini);
void	parsing(char *str, t_mini *mini);
void	add_last_token(char *str, t_mini *mini, int type);

/*---------------------------------- Error ----------------------------------*/

void	show_error(char *str);

#endif