#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naali <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 11:18:25 by naali             #+#    #+#              #
#    Updated: 2019/07/26 04:46:32 by nabih            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

rose			=	\033[1;31m
neutre			=	\033[0m
vertfonce		=	\033[0;32m

NAME			=	libft.a

AR				=	ar

ARFLAGS			=	rcs

CC				=	gcc

OBJ_PATH		=	./objs

CFLAGS			=	-Wall -Wextra -Werror

INCLUDE			=	-I./includes

SRC				=	ft_atoi.c			ft_bzero.c			ft_isalnum.c		ft_isalpha.c		ft_isascii.c	\
					ft_isdigit.c		ft_isprint.c		ft_memccpy.c		ft_memchr.c			ft_memcmp.c		\
					ft_memcpy.c			ft_memmove.c		ft_memset.c			ft_strcat.c			ft_strchr.c		\
					ft_strcmp.c			ft_strcpy.c			ft_strdup.c			ft_strlcat.c		ft_strlen.c		\
					ft_strncat.c		ft_strncmp.c		ft_strncpy.c		ft_strnstr.c		ft_strrchr.c	\
					ft_strstr.c			ft_tolower.c		ft_toupper.c		ft_memalloc.c		ft_memdel.c		\
					ft_strnew.c			ft_strdel.c			ft_strclr.c			ft_striter.c		ft_striteri.c	\
					ft_strmap.c			ft_strmapi.c		ft_strequ.c			ft_strnequ.c		ft_strsub.c		\
					ft_strjoin.c		ft_strtrim.c		ft_strsplit.c		ft_itoa.c			ft_putchar.c	\
					ft_putstr.c			ft_putendl.c		ft_putnbr.c			ft_putchar_fd.c		ft_putstr_fd.c	\
					ft_putendl_fd.c		ft_putnbr_fd.c		ft_lstnew.c			ft_lstdelone.c		ft_lstdel.c		\
					ft_lstadd.c			ft_lstiter.c		ft_lstmap.c			ft_lstlast.c		ft_lstfind.c	\
					ft_lstsize.c		ft_lstfindsize.c	ft_strndup.c		get_next_line.c

OBJ				=	$(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))

#******************************************************************************#

vpath %.c ./srcs/:

all				:	$(NAME)

$(NAME)			:	$(OBJ)
					@echo "${vertfonce}Compiling ...${neutre}\c"
					@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
					@echo "${rose}DONE${neutre}"

$(OBJ_PATH)/%.o	:	%.c
					@mkdir $(OBJ_PATH) 2> /dev/null || true
					@echo "${vertfonce}Creating $@ ...\c${neutre}"
					@$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)
					@echo "${rose}DONE${neutre}"

clean			:
					@echo "${rose}Cleaning LIBFT ...${neutre}\c"
					@rm -rf $(OBJ_PATH)
					@echo "${vertfonce}DONE${neutre}"

fclean			:	clean
					@echo "${rose}Fcleaning LIBFT ...${neutre}\c"
					@rm -rf $(NAME)
					@echo "${vertfonce}DONE${neutre}"

re				:	fclean all
