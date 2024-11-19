SRCS = srcs/main.c srcs/player.c srcs/hooks.c srcs/freem.c srcs/init.c srcs/default.c srcs/utils.c \
		${RYCST} ${MAP}

RYCST = srcs/raycast/raycast.c srcs/raycast/raycast_h.c srcs/raycast/raycast_v.c srcs/raycast/raycast_utils.c

MAP = srcs/map/map.c srcs/map/mapfile.c srcs/map/mapcolor.c

INC = -I./includes -I./mlx -I./libft

OBJS = ${SRCS:.c=.o}

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror

OPTIF = -pthread -g -finline-functions -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -march=native

all: ${NAME}

.c.o:
	gcc ${CFLAGS} ${INC} ${OPTIF} -c $< -o ${<:.c=.o}

clean:
	make -C ./libft clean
	make -C ./mlx clean
	rm -rf ${OBJS}

fclean: clean
	make -C ./libft fclean
	rm -rf ${NAME}

re: fclean all

${NAME}: ${OBJS}
	@make -C ./mlx all
	@make -C ./libft bonus
	gcc ${CFLAGS} ${OBJS} ${OPTIF} -Lmlx -lmlx -lXext -lX11 -lm -lz -Llibft -l:libft.a ${INC} -o ${NAME}

.PHONY: all clean fclean re
