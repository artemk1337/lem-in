# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 18:26:35 by cchadwic          #+#    #+#              #
#    Updated: 2020/03/02 15:51:56 by cchadwic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS_NAME = main.c\
			init.c\
			hash.c\
			error_handler.c\
			validation.c\
			_check.c\
			clear.c\
			solutions.c\
			solutions_copy.c\
            check_solutions.c\
			output.c\
			sort_solutions.c\



### PATH ###
SRCS_PATH = src/
OBJ_PATH  = obj/
LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

FLAGS = -Wall \
		-Werror \
		-Wextra \
		-ftrapv \
		-Wfloat-equal \
		-Wundef \
		-Wshadow \
		-Wpointer-arith \
		-Wcast-qual \
		-Wno-missing-braces \
		-Wcast-align \
		-Wunreachable-code \
		-D_FORTIFY_SOURCE=2 \
		-fstack-protector-strong \
		-Werror=format-security \
		-Wformat=2 # Check printf \
		# -finstrument-functions \
		# -Wmissing-prototypes \
		# -Wstrict-prototypes \

HEADERS = ./inc
INC = -I $(HEADERS) -I ./$(LIBFT_PATH)includes/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@gcc $(FLAGS) $(OBJ) $(INC) -L $(LIBFT_PATH) -lft -g -o $(NAME)
	@echo "\033[32mBinary\t\t\\033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c $(HEADERS)/*
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@
	@echo "\033[34m\033[1mCompilation of\t\033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

$(LIBFT):
	@make -C $(LIBFT_PATH)

clean:
	@make -C $(LIBFT_PATH)/ clean
	@/bin/rm -rf $(OBJ_PATH)
	@echo "\033[31mObjects files\t\033[1;31m$(OBJ)\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@/bin/rm -rf $(NAME)
	@echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re

# URLs for compiler flags
# https://developers.redhat.com/blog/2018/03/21/compiler-and-linker-flags-gcc/
# https://stackoverflow.com/questions/3375697/useful-gcc-flags-for-c
