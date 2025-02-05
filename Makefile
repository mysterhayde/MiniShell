NAME = minishell
CC = cc
RM = rm -rf
FLAGS = -Werror -Wextra -Wall -g -fsanitize=leak
MAKE := make --no-print-directory

SRC_DIR  = src/
MAIN_SRC =	main.c \
			show_error.c
SRC = $(addprefix $(SRC_DIR), $(MAIN_SRC))

INIT_SRC = init.c
INIT_DIR = src/init/
INIT = $(addprefix $(INIT_DIR), $(INIT_SRC))

CMDS_SRC = pwd.c cd.c env.c echo.c exit.c
CMDS_DIR = src/cmds/
CMDS = $(addprefix $(CMDS_DIR), $(CMDS_SRC))

EXEC_SRC = execute.c builtin.c bin.c path.c pipe.c
EXEC_DIR = src/exec/
EXEC = $(addprefix $(EXEC_DIR), $(EXEC_SRC))

PARS_SRC = parsing.c check_operator.c split_entry.c
PARS_DIR = src/parsing/
PARS = $(addprefix $(PARS_DIR), $(PARS_SRC))

ALL_SRC = $(SRC) $(INIT) $(CMDS) $(PARS) $(EXEC)

LIBFT_A = libft.a
LIBFT_DIR = libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_A))
# PRINTF_A = libftprintf.a
# PRINTF_DIR = libft/printf/
PRINTF = $(addprefix $(PRINTF_DIR), $(PRINTF_A))
OBJS = $(ALL_SRC:.c=.o)

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

$(NAME): $(OBJS)
	@echo $(CURSIVE)$(GRAY) " - Making libft..." $(NONE)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo $(CURSIVE)$(GRAY) " - Compiling $(NAME)..." $(NONE)
	@cc $(FLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME) -lreadline -lhistory
	@echo $(GREEN)"- Compiled -"$(NONE)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	@echo $(CURSIVE)$(GRAY) " -> Cleaning object files.." $(NONE)
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo $(CURSIVE)$(GRAY) " -> Removing $(NAME)" $(NONE)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus