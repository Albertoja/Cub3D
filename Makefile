SRCS	= main.c ft_print_matrix.c get_next_line.c get_next_line_aux.c ft_parse_map.c ft_cub3d_aux.c ft_free_matrix.c ft_check_map01.c ft_check_map02.c ft_error.c ft_clean_map.c ft_cube.c ft_load_tex.c ft_key.c

OBJS	= ${SRCS:.c=.o}

NAME	= cub3D

MINILIB	= mlx/libmlx.a

PATHMLIB	= mlx/

PATHLIB	= libft/

LIBFT	= libft/libft.a

CC	= gcc

RM	= rm -f

CFLAGS	= -I. -Wall -Wextra -Werror -Imlx #-g3 -fsanitize=address # con el sanitize puesto va todo mas lento

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
				@make -C ${PATHLIB}
				@make -C ${PATHMLIB}
				${CC} ${CFLAGS} ${MINILIB} ${LIBFT} ${OBJS} -L./mlx -lmlx -framework OpenGL -framework AppKit -L. -o ${NAME}

all:		${NAME}

clean:
				@make clean -C ${PATHLIB}
				@make clean -C ${PATHMLIB}
				${RM} ${OBJS}

fclean: 	clean
				@make clean
				${RM} ${LIBFT}
				${RM} ${MINILIB}
				${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean re
