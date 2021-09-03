# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/18 18:07:55 by mdiallo           #+#    #+#              #
#    Updated: 2021/07/07 16:26:16 by mdiallo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

INFILE = infile

OUTFILE = outfile

NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRC_PATH = src

SRC_NAME = free_mem.c \
			search_path.c \
			create_lst.c \
			ft_split.c \
			pipex.c \
			pipex_2.c \
			pipex_3.c \
			gnl.c

CPPFLAGS = -I include

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

	@touch $(INFILE) $(OUTFILE)
	@echo "$(INFILE) and $(OUTFILE) made"

$(NAME): $(OBJ)
	@echo $(NAME) ": Sources compiling..."
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Executable "$(NAME)" made"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ) $(INFILE) $(OUTFILE)
	@rm -rf $(OBJ_PATH) || true
	@echo "$(OBJ_PATH) supprimé !"
	@echo "$(INFILE) $(OUTFILE) supprimé !"

fclean: clean
	@rm -f $(NAME)
	@echo "Executable de "$(NAME)" supprimé !"

re: fclean all
	@echo "Make re done !"