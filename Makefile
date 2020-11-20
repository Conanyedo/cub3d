# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 15:10:16 by ybouddou          #+#    #+#              #
#    Updated: 2020/11/20 13:40:20 by ybouddou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libcub3d.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = Utils/ft_memset.c\
	  Utils/ft_strncmp.c\
	  Utils/ft_atoi.c\
	  Utils/ft_split.c\
	  Utils/ft_putchar_fd.c\
	  Utils/ft_putstr_fd.c\
	  Utils/get_next_line.c\
	  Utils/get_next_line_utils.c\
	  cub3d.c\
	  func.c\
	  functions.c\
	  map_parsing.c\
	  map_checker.c\
	  parsing.c\
	  errors.c\
	  keys.c\
	  drawing.c\
	  spawning.c\
	  sprite.c\
	  bmp.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(OBJ) -lmlx -framework OpenGL -framework AppKit

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all