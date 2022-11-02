SRCS    = 	main.c\
		builtins/builtins_utils.c\
		parsing/lexer.c\
		utils_lst.c\
		parsing/clean_lst.c\
		builtins/builtins.c\

DIR_SRC_MINISHELL = ./sources/srcs_minishell/

OBJ	= ${SRCS:.c=.o}

DIR_OBJ = sources/objs/
OBJS = $(addprefix $(DIR_OBJ), $(OBJ))

DEP = ${SRCS:.c=.d}
DEPS = $(addprefix $(DIR_OBJ), $(DEP))

NAME = minishell

HEADERS	= -I includes
CC		= gcc
CFLAGS	= -MMD -Wall -Wextra -Werror -g



${NAME} : minishell

minishell :	${OBJS}
			make -C ./sources/libft
			${CC} ${CFLAGS} ${OBJS} ./sources/libft/libft.a -o ${NAME} -lreadline

all :		minishell

clean:
			rm -f ${OBJS} ${DEPS}
			make -C ./sources/libft clean

fclean:		clean
			rm -f minishell
			make -C ./sources/libft fclean

re:			fclean all

$(DIR_OBJ)%.o: $(DIR_SRC_MINISHELL)%.c 
	${CC} ${CFLAGS} -c $< ${HEADERS} -o $@



-include ${DEPS}

.PHONY: all clean fclean re