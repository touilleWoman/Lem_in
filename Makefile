#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naali <naali@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 16:13:53 by naali             #+#    #+#              #
#    Updated: 2019/11/29 14:18:37 by naali            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

rose			=	\033[1;31m
neutre			=	\033[0m
vertfonce		=	\033[0;32m

NAME			=	lem-in

CC				=	gcc

CFLAG 			=	-Wall -Wextra -Werror

INCLUDES		=	-I./includes	\
					-I./libft

OBJ_PATH		=	./objs

SRC				=	main.c				\
					lem_tab.c			\
					lem_path.c			\
					lst_node.c			\
					lst_path.c			\
					hash_encryption.c

SRC				+=	get_info.c			\
					get_nb_ants.c		\
					get_nodes.c			\
					get_paths.c

SRC				+=	solver.c 			\
					lst_address.c		\

OBJ 			=	$(addprefix $(OBJ_PATH)/, $(SRC:%.c=%.o))

LIB_PATH		=	-L./libft

LIBS 			=	-lft

LFLAG			=	$(LIB_PATH) $(LIBS)

######################################################################

vpath %.c ./srcs/:

all				:	libs $(NAME)

$(NAME)			:	$(OBJ)
					@echo "${vertfonce}Compiling ...${neutre}\c"
					@$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(LFLAG) $(INCLUDES) -g #-fsanitize=address
					@echo "${rose}DONE${neutre}"

$(OBJ_PATH)/%.o	:	%.c
					@mkdir $(OBJ_PATH) 2> /dev/null || true
					@echo "${vertfonce}Creating $@ ...\c${neutre}"
					@$(CC) $(CFLAG) -o $@ -c $< $(INCLUDES)
					@echo "${rose}DONE${neutre}"

clean			:
					@echo "${rose}Cleaning the project ...${neutre}\c"
					@make clean -C libft
					@rm -rf $(OBJ_PATH)
					@echo "${vertfonce}DONE${neutre}"

fclean			:	clean
					@echo "${rose}Fcleaning the project ...${neutre}\c"
					@make fclean -C libft
					@rm -rf $(NAME)
					@echo "${vertfonce}DONE${neutre}"

libs			:
					make -C ./libft/

re				:	fclean all

.PHONY			:	all clean fclean re image
