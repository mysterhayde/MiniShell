/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:10:09 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/22 02:48:46 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
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
# define ERR_PERMISSION	"permiss`ion denied"
# define ERR_TOOMANY	"too many arguments"
# define ERR_NOVALID	"not a valid identifier"
# define ERR_NOTNUMERIC	"numeric argument required"
# define ERR_NODIR		"No such file or directory"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define HISTORY_FILE ".minishell_history"

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
	LEFT_PAREN	= 10,
	RIGHT_PAREN	= 11
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

/**
 * @brief Structure to store state for token execution
 */
typedef struct s_state
{
	t_token	*original_token;
	t_bool	original_is_pipe;
	int		original_pipe_num;
}	t_state;

typedef struct s_mini
{
	char		**envp;
	char		*user;
	char		*cur_path;
	int			pipe_num;
	t_bool		is_pipe;
	t_token		*token;
	t_token		*backup;
	t_token		*last_cmd;
	int			exit;
	int			ret;
}	t_mini;

extern int	g_signo;

/*---------------------------------- INIT ------------------------------------*/

void	getcurpath(t_mini *mini);
void	setupenv(t_mini *mini, char **envp);
void	init_readline_history(t_mini *mini);
void	add_to_history(t_mini *mini, const char *command);
void	cleanup_history(void);
void	load_history_from_file(t_mini *mini);
void	save_history_to_file(t_mini *mini, const char *command);
void	process_history_lines(char **lines);
char	*get_history_path(t_mini *mini);
int		setup_signal_handlers(void);
void	reset_signals_for_child(void);
int		check_signal_interrupt(void);
char	*get_prompt(t_mini *mini);
void	free_env_arr(char **env);

/*--------------------------------- Builtins --------------------------------*/

int		pwd(t_mini *mini);
int		cd(t_mini *mini, char **cmd);
char	*expand_tilde(char *path, char **envp);
int		env(t_mini *mini);
char	*get_env_value(char **env, const char *name);
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
char	*expand(char *str, char **envp);

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
int		process_single_redir(t_token *current);
t_token	*create_command_sublist(t_token *start, t_token *end);
int		check_paren_balance(t_token *token);
int		apply_paren_redirections(t_token *token);
t_token	*find_next_logical_op(t_token *token);
int		exec_logical_ops(t_mini *mini, t_token *token);
int		exec_paren_expr(t_mini *mini, t_token *token);
t_token	*find_next_logical(t_token *token);
t_token	*find_matching_paren(t_token *token);
t_bool	has_parentheses(t_token *token);
t_token	*skip_paren_expr(t_token *token);
t_token	*find_next_logical_op_with_parens(t_token *token);
int		exec_logical_op_with_parens(t_mini *mini, t_token *token);
int		exec_paren_logical_ops(t_mini *mini, t_token *token);
int		exec_paren_with_redir(t_mini *mini, t_token *token);
int		exec_logical_with_redir(t_mini *mini, t_token *token);
t_bool	has_logical_ops(t_token *token);
void	save_exec_state(t_mini *mini, t_state *state);
void	restore_exec_state(t_mini *mini, t_state *state);
int		exec_sublist(t_mini *mini, t_token *sublist);
t_token	*copy_token(t_token *token);

/*---------------------------------- Path -----------------------------------*/

char	*find_path(char *cmd, char **envp);

/*--------------------------------- Parsing ---------------------------------*/

int		count_leading_spaces(char *str);
int		parsing(char *str, t_mini *mini);
int		check_final_token(t_token *token);
int		is_operator(t_mini *mini, char *str);
int		find_next_quote(char *str, char quote);
int		skip_until_next_quote(char *str, char quote, int i);

char	*clean_quote(char *str);
char	*find_next_token(char *str, int *i);
char	*search_variable(char *str, char **envp, int *error);

void	free_cmd_arr(char **cmd);
void	modify_str(t_mini *mini);
void	free_tokens(t_token *token);
void	free_token_list(t_mini *mini);
void	add_last_token(char *str, t_mini *mini, int type);

size_t	expanded_size(char *str, char **envp);

/*---------------------------- Before Redirection ---------------------------*/

char	**sort_wildcard_tab(char **tab);
char	**search_wildcard(t_token *token);
char	*expand_string(char *str, char **envp);
char	**read_dir(char *pwd, char **wildcard_tab, int args);

int		ft_tablen(char **tab);
int		check_string(t_mini *mini, t_token *cmd_token);
int		split_wildcard(char *wildcard, char ***wildcard_tab);

void	fix_index(t_token *cmd_token);

/*------------------------------- Redirection -------------------------------*/

int		here_doc(char *limiter);
void	here_doc_child(char *limiter, int temp_fd);
int		create_temp_file(char **temp_name);
char	*generate_temp_name(int counter);

/*---------------------------------- Error ----------------------------------*/

void	free_all(t_mini *mini);
void	show_err_msg(char *cmd, char *error);
void	show_error_exit(char *cmd, char *error, int code);
int		show_err_return(char *cmd, char *err, int code);
void	show_cmd_not_found(char *cmd);

#endif
