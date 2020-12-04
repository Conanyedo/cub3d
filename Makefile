# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 15:10:16 by ybouddou          #+#    #+#              #
#    Updated: 2020/11/30 17:38:48 by ybouddou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
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

SRCb = Utils/ft_memset.c\
	   Utils/ft_strncmp.c\
	   Utils/ft_atoi.c\
	   Utils/ft_split.c\
	   Utils/ft_putchar_fd.c\
	   Utils/ft_putstr_fd.c\
	   Utils/get_next_line.c\
	   Utils/get_next_line_utils.c\
	   Bonus/cub3d_bonus.c\
	   Bonus/func_bonus.c\
	   Bonus/functions_bonus.c\
	   Bonus/map_parsing_bonus.c\
	   Bonus/map_checker_bonus.c\
	   Bonus/parsing_bonus.c\
	   Bonus/errors_bonus.c\
	   Bonus/keys_bonus.c\
	   Bonus/drawing_bonus.c\
	   Bonus/spawning_bonus.c\
	   Bonus/sprite_bonus.c\
	   Bonus/bmp_bonus.c\
	   Bonus/minimap_bonus.c\
	   Bonus/resize_map_bonus.c\
	   Bonus/lifebar_bonus.c\
	   Bonus/floor_ceiling_bonus.c\
	   Bonus/weapon_bonus.c\
	   Bonus/fire_bonus.c\
	   Bonus/bullets_bonus.c\
	   Bonus/add_bonus.c\

OBJ = $(SRC:.c=.o)

OBJb = $(SRCb:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

bonus: $(OBJb)
	@$(CC) $(CFLAGS) $(OBJb) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -rf $(OBJ) $(OBJb)

fclean: clean
	@rm -rf $(NAME)

re: fclean all