NAME 		= cub3d

SRCS		=	\
			src/main.c \
			src/mlx_functions.c \
			src/error/error.c \
			src/utils/utils.c \
			src/utils/free.c \
			src/utils/ft_split.c \
			src/utils/get_next_line.c \
			src/parse/read_file.c \
 			src/parse/colors.c \
			src/parse/check_colors.c \
 			src/parse/textures.c \
 			src/parse/map.c \
 			src/parse/map_temp.c \
			src/parse/check_map.c \
			src/raycasting/raycasting.c \


OBJS		= $(SRCS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror -g

UNAME		= $(shell uname)

ifeq ($(UNAME), Linux)
	OFLAGS		= $(CFLAGS) -L ./mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MLX			= ./mlx_linux
else
	OFLAGS		= $(CFLAGS) -L ./mlx -l mlx -framework OpenGl -framework Appkit
	MLX			= ./mlx
endif

.c.o:
			@cc $(CFLAGS) -c $< -o $(<:.c=.o) -I ./includes

$(NAME):	$(OBJS)
				@make -C $(MLX) &> /dev/null
				cc $(OBJS) $(OFLAGS) -o $(NAME)

all:		$(NAME)

clean:
			rm -rf $(OBJS)
			@make clean -C $(MLX)

fclean:		clean
				rm -rf $(NAME)
				rm -rf *.dSYM

re:			fclean all

.PHONY:		re fclean clean all
