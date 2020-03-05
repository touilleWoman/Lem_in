#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naali <naali@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 16:13:53 by naali             #+#    #+#              #
#    Updated: 2020/01/03 15:16:25 by naali            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

rose			=	\033[1;31m
neutre			=	\033[0m
vertfonce		=	\033[0;32m

NAME			=	lem-in

CC				=	gcc

CFLAG 			=	-Wall -Wextra -Werror

INC_FLAG		=	-I

HEADERS_PATH	=	./includes		\
					./libft

HEADERS			=	includes.h		\
					lem_in.h		\
					get_info.h		\
					solver.h		\
					get_many_path.h	\
					libft.h

INCLUDES		=	$(addprefix $(INC_FLAG), $(HEADERS_PATH))

OBJ_PATH		=	./objs

SRC				=	main.c				\
					lem_tab.c			\
					lst_node.c			\
					lst_node_bis1.c		\
					lst_node_bis2.c		\
					lst_path.c			\
					lst_path_bis1.c		\
					lst_path_bis2.c		\
					lst_path_bis3.c		\
					hash_encryption.c

SRC				+=	get_info.c			\
					get_nb_ants.c		\
					get_nodes.c			\
					get_paths.c			\
					ant_lst.c

SRC				+=	solver.c 			\
					solver_bis.c		\
					lst_address.c		\
					print_ants.c		\
					get_appro_max.c		\
					fulkerson_algo.c	\
					cross_road.c		\
					retrace_circuits.c	\
					how_many_path.c		\


OBJ 			=	$(addprefix $(OBJ_PATH)/, $(SRC:%.c=%.o))

LIB_PATH		=	-L./libft

LIBS 			=	-lft

LFLAG			=	$(LIB_PATH) $(LIBS)

######################################################################

vpath %.c ./srcs/:
vpath %.h ./includes/:./libft/

all				:	libs $(NAME)

$(NAME)			:	$(OBJ) ./libft/libft.a
					@echo "${vertfonce}Compiling ...${neutre}\c"
					@$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(LFLAG) $(INCLUDES)
					@echo "${rose}DONE${neutre}"

$(OBJ_PATH)/%.o	:	%.c $(HEADERS)
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
