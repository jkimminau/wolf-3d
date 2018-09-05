# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/31 01:00:58 by jkimmina          #+#    #+#              #
#    Updated: 2018/09/04 18:48:19 by jkimmina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = gcc 

CFLAGS = -Wall -Wextra -Werror

SRC =		src/wolf3d.c	\
			src/init.c		\
			src/event.c		\
			src/read.c		\
			src/draw.c		\
			src/move.c		\

HEADER_DIR =	.			\

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a
LIBFTH = libft/libft.h
LIBFTLNK = -L libft/ -l ft

MLX = minilibx/libmlx.a
MLXH = minilibx/mlx.h
MLXLNK = -L minilibx/ -l mlx -framework OpenGL -framework AppKit

all : $(NAME)

$(LIBFT):
	make -C libft/

$(MLX):
	make -C minilibx/

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -I .
	mv *.o src

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(OBJ) -o $(NAME) $(LIBFTLNK) $(MLXLNK)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	make fclean -C libft/
	make clean -C minilibx/
	rm -rf $(NAME)

re: fclean all
