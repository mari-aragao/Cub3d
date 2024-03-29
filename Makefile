NAME 		= cub3d

SRCS		=	\
			src/main.c \
			src/mlx_func.c \
			src/mlx_func2.c \
			src/error/error.c \
			src/utils/utils.c \
			src/utils/utils2.c \
			src/utils/converter.c \
			src/utils/free.c \
			src/utils/ft_split.c \
			src/utils/get_next_line.c \
			src/utils/get_next_line_utils.c \
			src/parse/read_file.c \
 			src/parse/colors.c \
			src/parse/check_colors.c \
 			src/parse/textures.c \
			src/parse/read_texture.c \
 			src/parse/map.c \
 			src/parse/map_temp.c \
			src/parse/check_map.c \
			src/parse/check_map2.c \
			src/raycasting/rayc.c \
			src/raycasting/rayc2.c \
			src/raycasting/init_rayc_vars.c \
			src/raycasting/move_player.c \
			src/raycasting/rotate_player.c \


OBJS		= $(SRCS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror -g

UNAME		= $(shell uname)

OFLAGS		= $(CFLAGS) -L ./mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

MLX			= ./mlx_linux

.c.o:
			@cc $(CFLAGS) -c $< -o $(<:.c=.o) -I ./includes

$(NAME):	$(OBJS)
				@make -C $(MLX)
				@cc $(OBJS) $(OFLAGS) -o $(NAME)

all:		$(NAME)

clean:
			rm -rf $(OBJS)
			@make clean -C $(MLX)

fclean:		clean
				rm -rf $(NAME)
				rm -rf *.dSYM

re:			fclean all

.PHONY:		re fclean clean all
