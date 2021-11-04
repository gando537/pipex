# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/18 18:07:55 by mdiallo           #+#    #+#              #
#    Updated: 2021/11/04 18:17:40 by mdiallo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = pipex

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRC_PATH = src

SRCS = src/free_mem.c \
			src/search_path.c \
			src/create_lst.c \
			src/ft_split.c \
			src/pipex.c \
			src/pipex_2.c \
			src/pipex_3.c \
			src/gnl.c

BONUS = src/free_mem.c \
		src/search_path.c \
		src/create_lst.c \
		src/ft_split.c \
		src/pipex_bonus.c \
		src/pipex_2.c \
		src/pipex_3.c \
		src/gnl.c

CPPFLAGS = -I include

OBJS	=	$(SRCS:.c=.o)

OBJS_B	=	$(BONUS:.c=.o)

all		:	$(NAME)

bonus	:	$(OBJS_B)
	@echo "bonus: Sources compiling..."
	@$(CC) $(CFLAGS) $^ -o $(NAME)
	@echo "Executable "$(NAME)" made"

$(NAME)	:	$(OBJS)
	@echo $(NAME) ": Sources compiling..."
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Executable "$(NAME)" made"

%.o		:	%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean	:
	@rm -f $(OBJS) $(OBJS_B)
	@echo "Fichiers objets supprimés !"

fclean	:	clean 
	@rm -f $(NAME)
	@echo "Executable de "$(NAME)" supprimé !"

re		:	fclean all


