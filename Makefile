NAME = minishell
CC = cc
RM = rm -rf
FLAGS = -Werror -Wextra -Wall -g3

SRC = $(MAIN_SRC)
MAIN_SRC = main.c 

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
	@make -C $(LIBFT_DIR)
	@echo $(CURSIVE)$(GRAY) " - Compiling $(NAME)..." $(NONE)
	cc $(FLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJS): $(SRC)
	@echo $(CURSIVE)$(GRAY) " - Making object files..." $(NONE)
	@$(CC) $(FLAGS) -c $(SRC)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	@echo $(CURSIVE)$(GRAY) " -> Cleaning object files.." $(NONE)
	@$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	@echo $(CURSIVE)$(GRAY) " -> Removing $(NAME) and $(CHECKER)..." $(NONE)
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus