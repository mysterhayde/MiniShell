# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 21:12:44 by hdougoud          #+#    #+#              #
#    Updated: 2024/12/16 14:17:50 by hdougoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
GCC = cc
CFLAGS = -Wall -Werror -Wextra

#--------------------------------------DIRECTORY-------------------------------

LIBFT_DIR	= Libft
PRINTF_DIR	= Printf
GNL_DIR		= Get_next_line

#--------------------------------------SOURCES---------------------------------

#LIBFT_SOURCES
LIBFT_SRCS = 	$(LIBFT_DIR)/ft_isascii.c	$(LIBFT_DIR)/ft_memcpy.c 		$(LIBFT_DIR)/ft_putstr_fd.c \
				$(LIBFT_DIR)/ft_strlcat.c	$(LIBFT_DIR)/ft_strrchr.c		$(LIBFT_DIR)/ft_atoi.c \
				$(LIBFT_DIR)/ft_isdigit.c	$(LIBFT_DIR)/ft_memmove.c		$(LIBFT_DIR)/ft_split.c \
				$(LIBFT_DIR)/ft_strlcpy.c	$(LIBFT_DIR)/ft_strtrim.c		$(LIBFT_DIR)/ft_bzero.c \
				$(LIBFT_DIR)/ft_isprint.c	$(LIBFT_DIR)/ft_memset.c 		$(LIBFT_DIR)/ft_strchr.c \
				$(LIBFT_DIR)/ft_strlen.c	$(LIBFT_DIR)/ft_substr.c 		$(LIBFT_DIR)/ft_calloc.c \
				$(LIBFT_DIR)/ft_itoa.c		$(LIBFT_DIR)/ft_putchar_fd.c	$(LIBFT_DIR)/ft_strdup.c \
				$(LIBFT_DIR)/ft_strmapi.c	$(LIBFT_DIR)/ft_tolower.c		$(LIBFT_DIR)/ft_isalnum.c \
				$(LIBFT_DIR)/ft_memchr.c	$(LIBFT_DIR)/ft_putendl_fd.c 	$(LIBFT_DIR)/ft_striteri.c \
				$(LIBFT_DIR)/ft_strncmp.c	$(LIBFT_DIR)/ft_toupper.c		$(LIBFT_DIR)/ft_isalpha.c \
				$(LIBFT_DIR)/ft_memcmp.c	$(LIBFT_DIR)/ft_putnbr_fd.c		$(LIBFT_DIR)/ft_strjoin.c \
				$(LIBFT_DIR)/ft_strnstr.c	$(LIBFT_DIR)/ft_atol.c			$(LIBFT_DIR)/ft_safe_free.c

#BONUS_SOURCES
LIBFTBONUS =	$(LIBFT_DIR)/ft_lstadd_back_bonus.c \
				$(LIBFT_DIR)/ft_lstadd_front_bonus.c \
				$(LIBFT_DIR)/ft_lstlast_bonus.c \
				$(LIBFT_DIR)/ft_lstnew_bonus.c \
				$(LIBFT_DIR)/ft_lstsize_bonus.c \
				$(LIBFT_DIR)/ft_lstdelone_bonus.c \
				$(LIBFT_DIR)/ft_lstclear_bonus.c \
				$(LIBFT_DIR)/ft_lstiter_bonus.c \
				$(LIBFT_DIR)/ft_lstmap_bonus.c

#PRINTF_SOURCES
PRINTF_SRCS =	$(PRINTF_DIR)/ft_printf.c \
				$(PRINTF_DIR)/ft_print_numbers.c

#GET_NEXT_LINE
GNL_SRCS	=	$(GNL_DIR)/get_next_line.c \
				$(GNL_DIR)/get_next_line_utils.c

#ALL_SOURCES
SOURCES = 		$(LIBFT_SRCS) $(LIBFTBONUS) $(PRINTF_SRCS) $(GNL_SRCS)

#-------------------------------------OBJECTS----------------------------------

OBJECTS = 		$(SOURCES:.c=.o)		

#--------------------------------------COLOR-----------------------------------

GRAY	= \033[1;30m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
PURPLE	= \033[1;35m
CYAN	= \033[1;36m
WHITE	= \033[1;37m

#--------------------------------------RULES-----------------------------------

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)
	echo -e "$(GREEN)Libft done$(WHITE)"
	
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SILENT:
.PHONY: all clean fclean re