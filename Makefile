NAME = minishell
CC = cc
RM = rm -rf
FLAGS = -Werror -Wextra -Wall -g -fPIE
MAKE := make --no-print-directory

#--------------------------------------LIBFT------------------------------------#
LIBFT_A = libft.a
LIBFT_DIR = libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_A))
PRINTF = $(addprefix $(PRINTF_DIR), $(PRINTF_A))

#--------------------------------------SOURCES---------------------------------#
SRC_DIR = src/
MAIN_SRC = main.c \
 show_error.c \
 free_all.c
SRC = $(addprefix $(SRC_DIR), $(MAIN_SRC))

INIT_SRC = init.c history.c history_utils.c signal.c prompt_utils.c env_utils.c check_null.c
INIT_DIR = src/init/
INIT = $(addprefix $(INIT_DIR), $(INIT_SRC))

CMDS_SRC = pwd.c cd.c env.c echo.c exit.c unset.c export.c expand.c
CMDS_DIR = src/cmds/
CMDS = $(addprefix $(CMDS_DIR), $(CMDS_SRC))

EXEC_SRC = execute.c builtin.c bin.c path.c pipe.c exec_utils.c pipe_utils.c pipe_wait.c \
 redir.c redir2.c exec_redir.c operators.c operators2.c heredoc.c operator_state.c \
 heredoc_utils.c execute_cmd.c heredoc_post.c heredoc_pre.c heredoc_redir.c heredoc_utils2.c \
 pipe_heredoc_utils.c pipe_heredoc.c exec_heredoc.c heredoc_exec.c logical_heredoc.c heredoc_scan.c \
 pipe_redir_utils.c pipe_cmd_flags.c pipe_token_utils.c
EXEC_DIR = src/exec/
EXEC = $(addprefix $(EXEC_DIR), $(EXEC_SRC))

PARS_SRC = parsing.c parsing_utils.c split_entry.c tokens.c parenthesis.c \
 parenthesis_ops.c parenthesis_redir.c parenthesis_exec.c \
 token_utils.c parenthesis_utils.c
PARS_DIR = src/parsing/
PARS = $(addprefix $(PARS_DIR), $(PARS_SRC))

BEF_EXEC = check_string.c expand_string.c clear_quotes.c wildcard.c read_dir.c \
 wildcard_utils.c wildcard_cmp.c wildcard_getdir.c error_code.c
BEF_DIR = src/before_exec/
BEFORE = $(addprefix $(BEF_DIR), $(BEF_EXEC))

ALL_SRC = $(SRC) $(INIT) $(CMDS) $(PARS) $(EXEC) $(BEFORE)

#--------------------------------------OBJECTS----------------------------------#
OBJ_DIR = Objects/
# Generate object files with same names but in Objects directory
OBJECTS = $(patsubst %.c,$(OBJ_DIR)%.o,$(notdir $(ALL_SRC)))

# This is a crucial part - create variables for each source directory to make vpath work properly
VPATH = $(SRC_DIR):$(INIT_DIR):$(CMDS_DIR):$(PARS_DIR):$(EXEC_DIR):$(BEF_DIR)

#--------------------------------------ANIMATION CONFIG------------------------#
ANIMATION_FRAMES = ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏
ANIMATION_COLOR = '\033[1;36m'
TOTAL_FILES := $(words $(OBJECTS))

#--------------------------------------COLORS-----------------------------------#
NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
BLUE='\033[34m'
MAGENTA='\033[35m'
CYAN='\033[36m'
WHITE='\033[37m'
BOLD='\033[1m'

#--------------------------------------RULES-----------------------------------#
all: reset_counter $(OBJ_DIR) $(LIBFT) $(NAME)

reset_counter:
	@rm -f .counter
	@echo "0" > .counter

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo $(BOLD)$(MAGENTA)"Objects directory created"$(NONE)

$(LIBFT):
	@echo $(CURSIVE)$(GRAY)"🔧 Making libft..."$(NONE)
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(LIBFT) $(PRINTF) -o $(NAME) -lreadline
	@echo "\033[1;32m\n✅ $(NAME) successfully compiled!\n\033[0m"
	@rm .counter

#--------------------------------------COMPILATION RULE------------------------#
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@if [ ! -f .counter ]; then echo "0" > .counter; fi
	@file_count=$$(cat .counter); \
	file_count=$$((file_count + 1)); \
	echo $$file_count > .counter; \
	frames="⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏"; \
	frame_index=$$((file_count % 10)); \
	frame=$$(echo $$frames | cut -d ' ' -f $$((frame_index + 1))); \
	percent=$$((100 * file_count / $(TOTAL_FILES))); \
	barlen=30; \
	done=$$((barlen * percent / 100)); \
	todo=$$((barlen - done)); \
	bar=$$(printf "█%.0s" $$(seq 1 $$done)); \
	space=$$(printf "░%.0s" $$(seq 1 $$todo)); \
	printf "\r\033[1;36m%s \033[1mCompiling\033[0m [%-*s] %3d%% \033[36m%-40.40s\033[0m" "$$frame" "$$barlen" "$$bar$$space" "$$percent" "$<"; \
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo $(CURSIVE)$(GRAY) " -> Cleaning object files.." $(NONE)
	@$(RM) $(OBJ_DIR)
	@$(RM) .counter
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo $(CURSIVE)$(GRAY) " -> Removing $(NAME)" $(NONE)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus:
	@echo $(CURSIVE)$(GRAY) " - Compiling bonus $(NAME)..." $(NONE)
	@echo $(GREEN)"- Compiled -"$(NONE)

.PHONY: all clean fclean re bonus reset_counter