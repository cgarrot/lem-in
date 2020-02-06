# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/10 19:59:22 by seanseau     #+#   ##    ##    #+#        #
#    Updated: 2020/02/06 14:06:18 by seanseau    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = lemin
CC = gcc
DEBUG = -fsanitize=address
FLAGS = -Wall -Wextra -Werror -g
INC = include/lemin.h
HEADER = include
OPTI = -O3 -march=native -flto -ffast-math

#------------------------------------FILE--------------------------------------#

FILES = src/parser\
		src/parser_check\
		src/check_link_name\
		src/ft_list\
		src/utils\
		src/utils2\
		src/utils3\
		src/utils4\
		src/init\
		src/init2\
		src/set_all_tab\
		src/main\
		src/bfs1\
		src/setup_bfs\
		src/bfs2\
		src/function_matrix_state\
		src/bfs4\
		src/bfs5\
		src/bfs6\
		src/bfs7\
		src/display_algo\
		src/free\
		src/dispatch_ant\
		src/clear_path\

#----------------------------------SOURCE--------------------------------------#

SRC = $(addsuffix .c , $(FILES))

#----------------------------------OBJECT--------------------------------------#

OBJ = $(addsuffix .o , $(FILES))

#-----------------------------------RULE---------------------------------------#

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	@make -C libft/
	@$(CC) $(FLAGS) $(SRC) -L. libft/libftprintf.a -o $(NAME)


object/%.o: src/%.c $(INC)
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/

re: fclean all
