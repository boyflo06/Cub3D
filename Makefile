SRCS = srcs/main.c

INC = -I./includes -I./mlx -I./libft

OBJS = ${SRCS:.c=.o}

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

.c.o:
	gcc ${CFLAGS} ${INC} -g3 -O3 -c $< -o ${<:.c=.o}

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
	gcc ${CFLAGS} ${OBJS} -g3 -O3 -flto -ffast-math -march=native -Lmlx -lmlx -lXext -lX11 -lm -lz -Llibft -l:libft.a ${INC} -o ${NAME}

.PHONY: all clean fclean re
