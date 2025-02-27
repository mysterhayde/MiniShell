NAME = minishell
CC = cc
RM = rm -rf
FLAGS = -Werror -Wextra -Wall -g
MAKE := make --no-print-directory

#--------------------------------------LIBFT------------------------------------#

LIBFT_A = libft.a
LIBFT_DIR = libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_A))
PRINTF = $(addprefix $(PRINTF_DIR), $(PRINTF_A))

#--------------------------------------SOURCES---------------------------------#

SRC_DIR  = src/
MAIN_SRC =	main.c \
			show_error.c \
			free_all.c
SRC = $(addprefix $(SRC_DIR), $(MAIN_SRC))

INIT_SRC = init.c history.c history_utils.c signal.c prompt_utils.c
INIT_DIR = src/init/
INIT = $(addprefix $(INIT_DIR), $(INIT_SRC))

CMDS_SRC = pwd.c cd.c env.c echo.c exit.c unset.c export.c expand.c
CMDS_DIR = src/cmds/
CMDS = $(addprefix $(CMDS_DIR), $(CMDS_SRC))

EXEC_SRC = execute.c builtin.c bin.c path.c pipe.c exec_utils.c pipe_utils.c pipe_wait.c \
			redir.c redir2.c exec_redir.c operators.c operators2.c heredoc.c
EXEC_DIR = src/exec/
EXEC = $(addprefix $(EXEC_DIR), $(EXEC_SRC))


PARS_SRC = parsing.c parsing_utils.c split_entry.c bash_syntax.c tokens.c clear_string.c expand_string.c clear_quotes.c
PARS_DIR = src/parsing/
PARS = $(addprefix $(PARS_DIR), $(PARS_SRC))

ALL_SRC = $(SRC) $(INIT) $(CMDS) $(PARS) $(EXEC)

vpath %.c $(SRC_DIR) $(INIT_DIR) $(CMDS_DIR) $(PARS_DIR) $(EXEC_DIR)

#--------------------------------------OBJECTS----------------------------------#

OBJ_DIR = Objects/
OBJS = $(notdir $(ALL_SRC:.c=.o))
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJS))

#--------------------------------------COLORS-----------------------------------#

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

#--------------------------------------RULES-----------------------------------#

all:$(OBJ_DIR) $(LIBFT) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo $(CURSIVE)$(GRAY) " - Making libft..." $(NONE)
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJECTS)
	@echo $(CURSIVE)$(GRAY) " - Compiling $(NAME)..." $(NONE)
	@cc $(FLAGS) $(OBJECTS) $(LIBFT) $(PRINTF) -o $(NAME) -lreadline
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJ_DIR)%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo $(CURSIVE)$(GRAY) " -> Cleaning object files.." $(NONE)
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo $(CURSIVE)$(GRAY) " -> Removing $(NAME)" $(NONE)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus