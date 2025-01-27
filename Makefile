NAME = minishell
CC = cc
RM = rm -rf
FLAGS = -Werror -Wextra -Wall -g
MAKE := make --no-print-directory

SRC = src/$(MAIN_SRC)
MAIN_SRC = main.c 

INIT_SRC = init.c
INIT_DIR = src/init/
INIT = $(addprefix $(INIT_DIR), $(INIT_SRC))

CMDS_SRC = pwd.c cd.c env.c echo.c
CMDS_DIR = src/cmds/
CMDS = $(addprefix $(CMDS_DIR), $(CMDS_SRC))

LIBFT_A = libft.a
LIBFT_DIR = libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_A))
# PRINTF_A = libftprintf.a
# PRINTF_DIR = libft/printf/
PRINTF = $(addprefix $(PRINTF_DIR), $(PRINTF_A))
OBJS = *.o

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

$(NAME): $(OBJS)
	@echo $(CURSIVE)$(GRAY) " - Making libft..." $(NONE)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo $(CURSIVE)$(GRAY) " - Compiling $(NAME)..." $(NONE)
	@cc $(FLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJS): $(SRC) $(INIT) $(CMDS)
	@echo $(CURSIVE)$(GRAY) " - Making object files..." $(NONE)
	@$(CC) $(FLAGS) -c $(SRC) $(INIT) $(CMDS)

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