/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:10:09 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/31 11:06:51 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"

# define ERR_MALLOC		"memory allocation failed"
# define ERR_PERMISSION	"permission denied"
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
	t_bool			processed;
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
	int			pipe_num;
	t_token		**heredoc_tokens;
	int			heredoc_count;
	int			*heredoc_fds;
	t_bool		isheredoc;
	t_bool		is_pipe;
	t_token		*token;
	t_token		*backup;
	t_token		*last_cmd;
	int			exit;
	int			ret;
}	t_mini;

extern int	g_signo;

/*---------------------------------- INIT ------------------------------------*/


int		check_signal_interrupt(void);
int		setup_signal_handlers_fork();
int		handle_fork_signal(int status);
int		setup_signal_handlers(t_mini *mini);
void	reset_error_reporting(void);
void	mark_last_command_tokens(t_token *token);

void	cleanup_history(void);
void	free_env_arr(char **env);
void	getcurpath(t_mini *mini);
void	reset_signals_for_child(void);
void	setupenv(t_mini *mini, char **envp);
void	process_history_lines(char **lines);
void	init_readline_history(t_mini *mini);
void	load_history_from_file(t_mini *mini);
void	add_to_history(t_mini *mini, const char *command);
void	save_history_to_file(t_mini *mini, const char *command);

char	*get_prompt(t_mini *mini);
char	*get_history_path(t_mini *mini);

/*--------------------------------- Builtins --------------------------------*/

int		pwd(void);
int		echo(char **cmd);
int		env(t_mini *mini);
int		cd(t_mini *mini, char **cmd);
int		unset(t_mini *mini, char **cmd);
int		print_export_list(char	**envp);
int		export(t_mini *mini, char **cmd);
int		exit_builtin(t_mini *mini, char **cmd);
int		handle_exit_in_pipe(t_mini *mini, char **cmd);
int		match_var_name(const char *env_var, const char *var_name);

char	**copy_env(char **env);
char	*expand(char *str, char **envp);
char	*expand_tilde(char *path, char **envp);
char	**add_env_var(char **envp, char *new_var);
char	*get_env_value(char **env, const char *name);
char	**update_env_var(char **envp, char *var_name, char *new_var);

void	safe_exit(t_mini *mini, int exit_code);
void	child_process_exit(t_mini *mini, int status);

size_t	get_env_size(char **env);

t_bool	is_valid_identifier(char *str);

/*--------------------------------- Execute ---------------------------------*/

int		is_builtin(char *cmd);
int		minipipe(t_mini *mini);
int		exec_bin(t_mini *mini, char **cmd);
int		exec_builtin(t_mini *mini, char **cmd);
int		run_pipe_commands(t_mini *mini, t_pipe *p);
int		wait_pipe_children(t_mini *mini, t_pipe *p);
int		create_pipes(int pipe_count, int **pipe_fds);
int		wait_for_children(t_mini *mini, pid_t *pids);
int		exec_pipe_cmd(t_mini *mini, int i, int *pipe_fds);
t_bool	should_skip_token(t_token *token, t_bool is_last_cmd);

void	execute(t_mini *mini);
void	find_cmd(t_mini *mini);
void	file_access_failed(char *file);
void	close_all_pipes(int pipe_count, int *pipe_fds);

/*---------------------------------- Redir ----------------------------------*/

int		apply_redir(t_token *token);
int		exec_parenthesis(t_mini *mini);
int		open_file_input(char *filename);
int		open_file_output(char *filename);
int		open_file_append(char *filename);
t_bool	is_output_redir(t_token *token);
int		apply_pipe_redir_with_heredoc(t_mini *mini, t_token *token,
			t_bool is_last_cmd);
int		check_paren_balance(t_token *token);
int		process_single_redir(t_token *current);
int		apply_paren_redirections(t_token *token);
int		exec_sublist(t_mini *mini, t_token *sublist);
int		exec_paren_expr(t_mini *mini, t_token *token);
int		exec_logical_ops(t_mini *mini, t_token *token);
int		exec_redirections(t_mini *mini, t_token *token);
int		exec_paren_with_redir(t_mini *mini, t_token *token);
int		exec_paren_logical_ops(t_mini *mini, t_token *token);
int		exec_logical_with_redir(t_mini *mini, t_token *token);
int		exec_logical_op_with_parens(t_mini *mini, t_token *token);

void	save_std_fds(int saved_fd[2]);
void	restore_std_fds(int saved_fd[2]);
void	save_exec_state(t_mini *mini, t_state *state);
void	restore_exec_state(t_mini *mini, t_state *state);

t_bool	has_logical_ops(t_token *token);
t_bool	has_parentheses(t_token *token);

t_token	*copy_token(t_token *token);
t_token	*skip_paren_expr(t_token *token);
t_token	*find_next_logical(t_token *token);
t_token	*skip_redirections(t_token *token);
t_token	*find_next_logical_op(t_token *token);
t_token	*find_matching_paren(t_token *token);
t_token	*find_next_logical_op_with_parens(t_token *token);
t_token	*create_command_sublist(t_token *start, t_token *end);

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
char	*get_directory(char **wildcard, char **prefix);
char	**read_dir(char *pwd, int args, char *wildcard);

int		ft_tablen(char **tab);
int		search_wildcard_char(char *str);
int		check_string(t_mini *mini, t_token *cmd_token);
int		compare_wildcard_and_file(char *file, char *wildcard);

char	*search_error_code(int return_code, char *str);
char	*expand_error_code(char *str, int return_code);
char	*replace_error_code(char *str, int i, int return_code);

void	fix_index(t_token *cmd_token);

/*------------------------------- Redirection -------------------------------*/

int		count_heredocs(t_token *token);
int		create_temp_file(char **temp_name);
int		minipipe_with_heredoc(t_mini *mini);
int		scan_and_execute_heredocs(t_mini *mini);
int		is_delimiter(char *line, char *delimiter);
int		scan_and_execute_all_heredocs(t_mini *mini);
int		allocate_heredoc_arrays(t_mini *mini, int count);
int		exec_logical_ops_heredoc(t_mini *mini, t_token *token);
int		apply_redir_with_heredoc(t_mini *mini, t_token *token);
int		run_pipe_commands_with_heredoc(t_mini *mini, t_pipe *p);
int		handle_heredoc_redirection(t_mini *mini, t_token *token);
int		exec_pipe_cmd_with_heredoc(t_mini *mini, int i, t_pipe *p);
int		exec_paren_with_redir_heredoc(t_mini *mini, t_token *token);
int		exec_redirections_with_heredoc(t_mini *mini, t_token *token);
int		process_single_heredoc(t_mini *mini, t_token *current, int i);
int		exec_logical_with_redir_heredoc(t_mini *mini, t_token *token);
int		here_doc_with_num(t_mini *mini, char *limiter, int heredoc_num);
int		process_single_redir_with_heredoc(t_mini *mini, t_token *token);
int		process_remaining_cmds(t_mini *mini, t_token *tokens, t_bool condition);
int		process_remaining_cmds_heredoc(t_mini *mini, t_token *tokens,
			t_bool condition);

char	*generate_temp_name(int counter);
char	*create_heredoc_prompt(int heredoc_num);

void	free_heredoc_arrays(t_mini *mini);
void	reset_heredoc_processed_flags(t_token *token);
void	here_doc_child_with_num(t_mini *mini, char *limiter, int temp_fd,
			int heredoc_num);

t_bool	is_parenthesis_cmd(t_token *token);

t_token	*find_next_pipe_token(t_token *token);

/*---------------------------------- Error ----------------------------------*/

int		show_err_return(char *cmd, char *err, int code);

void	free_all(t_mini *mini);
void	show_cmd_not_found(char *cmd);
void	free_pipe_resources(t_pipe *p);
void	show_err_msg(char *cmd, char *error);
void	show_error_exit(char *cmd, char *error, int code);

#endif
