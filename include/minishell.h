/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:10:09 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/25 16:56:48 by cbopp            ###   ########.fr       */
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
# include <limits.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define ERR_MALLOC		"memory allocation failed"
# define ERR_PERMISSION	"permission denied"
# define ERR_TOOMANY	"too many arguments"
# define ERR_NOVALID	"not a valid identifier"
# define ERR_NOTNUMERIC	"numeric argument required"
# define ERR_NODIR		"no such file or directory"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define HISTORY_FILE ".history"

/*---------------------------------- ENUM ------------------------------------*/

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

/**
 * @brief Error codes
 * @enum ERR_GENERAL	= 1, General errors
 * @enum ERR_BUILTIN	= 2, Builtin error (misuse of shell builtins)
 * @enum ERR_EXEC		= 126, Command invoked cannot execute
 * @enum ERR_NOTFOUND	= 127, Command not found
 * @enum ERR_SIGBASE	= 128, Fatal error signal base
 * @enum ERR_SYNTAX		= 258, Syntax error
 */
typedef enum e_errorcode
{
	ERR_GENERAL		= 1,
	ERR_BUILTIN		= 2,
	ERR_EXEC		= 126,
	ERR_NOTFOUND	= 127,
	ERR_SIGBASE		= 128,
	ERR_SYNTAX		= 258
}	t_errorcode;

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
	LIMITER		= 7,
	AND_OP		= 8, // &&
	OR_OP		= 9, // ||
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
	t_bool			expand;
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
char	*get_history_file_path(void);
void	save_history_to_file(void);
void	load_history_from_file(void);
void	cleanup_history(void);
int		setup_signal_handlers(void);
void	reset_signals_for_child(void);
int		check_signal_interrupt(void);
char	*get_prompt(t_mini *mini);

/*--------------------------------- Builtins --------------------------------*/

int		pwd(t_mini *mini);
int		cd(t_mini *mini, char **cmd);
int		env(t_mini *mini);
int		match_var_name(const char *env_var, const char *var_name);
int		export(t_mini *mini, char **cmd);
char	**add_env_var(char **envp, char *new_var);
int		print_export_list(char	**envp);
char	**update_env_var(char **envp, char *var_name, char *new_var);
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

/*---------------------------------- Redir ----------------------------------*/
int		open_file_input(char *filename);
int		open_file_output(char *filename);
int		open_file_append(char *filename);
void	save_std_fds(int saved_fd[2]);
void	restore_std_fds(int saved_fd[2]);
int		apply_redir(t_token *token);
t_token	*skip_redirections(t_token *token);
int		exec_redirections(t_mini *mini, t_token *token);
t_token	*create_command_sublist(t_token *start, t_token *end);
t_token	*find_next_logical_op(t_token *token);
int		exec_logical_ops(t_mini *mini, t_token *token);
t_token	*copy_token(t_token *token);

/*---------------------------------- Path -----------------------------------*/
char	*find_path(char *cmd, char **envp);

/*--------------------------------- Parsing ---------------------------------*/

int		is_separator(char c);
int		is_operator(t_mini *mini, char *str);

char	**split_args(char *str);
char	**check_bash_syntax(char **split);

void	free_tokens(t_token *token);
void	free_token_list(t_mini *mini);
void	parsing(char *str, t_mini *mini);
void	add_last_token(char *str, t_mini *mini, int type);

/*---------------------------------- Error ----------------------------------*/

void	show_err_msg(char *cmd, char *error);
void	show_error_exit(char *cmd, char *error, int code);
int		show_err_return(char *cmd, char *err, int code);
void	show_cmd_not_found(char *cmd);

#endif