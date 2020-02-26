# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/17 18:24:03 by cchadwic          #+#    #+#              #
#    Updated: 2020/02/19 17:30:11 by cchadwic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Werror -Wextra

INCLUDE = -I ./includes

HEADER = libft.h\
		 get_next_line.h

SRC =	ft_strsplit.c   ft_strdup.c        ft_lstmap.c\
		ft_memset.c ft_strequ.c        ft_lstnew.c\
		ft_strsub.c ft_striter.c           ft_memalloc.c\
		ft_strtrim.c    ft_striteri.c          ft_memccpy.c\
		ft_tolower.c    ft_strjoin.c           ft_memchr.c\
		ft_toupper.c    ft_strlcat.c           ft_memcmp.c\
		ft_strncat.c    ft_strlen.c        ft_memcpy.c\
		ft_strncmp.c    ft_strmap.c        ft_memdel.c\
		ft_strncpy.c    ft_strmapi.c           ft_atoi.c\
		ft_strnequ.c    ft_memmove.c           ft_bzero.c\
		ft_strnew.c ft_putchar.c           ft_create_elem.c\
		ft_strnstr.c    ft_putchar_fd.c        ft_isalnum.c\
		ft_strrchr.c    ft_putendl.c           ft_isalpha.c\
		ft_strstr.c ft_putendl_fd.c        ft_isascii.c\
		ft_putstr.c ft_putnbr.c        ft_isdigit.c\
		ft_putstr_fd.c  ft_putnbr_fd.c         ft_isprint.c\
		ft_strcat.c ft_list_push_params.c  ft_itoa.c\
		ft_strchr.c ft_list_size.c         ft_list_at.c\
		ft_strclr.c ft_lstadd.c        ft_list_clear.c\
		ft_strcmp.c ft_lstdel.c        ft_list_last.c\
		ft_strcpy.c ft_lstdelone.c         ft_list_push_back.c\
		ft_strdel.c ft_lstiter.c           ft_list_push_front.c\
		get_next_line.c ft_strndup.c ft_atoul.c ft_isdigitstr.c\
		ft_isspace.c	ft_create_vector.c

OBJ = $(SRC:.c=.o)

DSRC = src/
DOBJ = obj/
DHEADER = includes/

CSRC = $(addprefix $(DSRC),$(SRC))
COBJ = $(addprefix $(DOBJ),$(OBJ))
CHEADER = $(addprefix $(DHEADER),$(HEADER))

all: $(NAME)

$(NAME): $(COBJ)
	@ar rc $(NAME) $?
	@ranlib $(NAME)
	@echo "\033[32mBinary\t\t\033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(DOBJ)%.o : $(DSRC)%.c $(CHEADER)
	@mkdir -p $(DOBJ)
	@gcc $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[34m\033[1mCompilation of \t\033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

clean:
	@/bin/rm -rf $(DOBJ)
	@echo "\033[31mObjects files \033[1;31m$(OBJ)\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME)
	@echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re
