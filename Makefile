SRCS    = 	parsing/main.c\
		parsing/lexer.c\
		parsing/utils_lst.c\
		parsing/clean_lst.c\
		parsing/clean_quotes.c\
		parsing/check_separators.c\
		parsing/build_tab_cmd.c\
		builtins/init_env.c\
		builtins/builtins_lst.c\
		builtins/builtins.c\
		builtins/builtins_utils.c\
		builtins/builtins_cmd_pwd.c\
		builtins/builtins_cmd_cd.c\
		builtins/builtins_cmd_echo.c\
		builtins/builtins_cmd_exit.c\
		builtins/builtins_utils2.c\
		builtins/builtins_cmd_env.c\
		builtins/builtins_cmd_export.c\
		builtins/builtins_cmd_export2.c\
		builtins/builtins_cmd_unset.c\
		exec/pipex.c

DIR_SRC_MINISHELL = ./sources/srcs_minishell/

OBJ	= ${SRCS:.c=.o}

DIR_OBJ = sources/objs/
OBJS = $(addprefix $(DIR_OBJ), $(OBJ))

DEP = ${SRCS:.c=.d}
DEPS = $(addprefix $(DIR_OBJ), $(DEP))

NAME = minishell

HEADERS	= -I includes
CC		= cc -fsanitize=address
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
