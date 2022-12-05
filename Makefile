# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRCS    = 	main.c\
		parsing/lexer.c\
		parsing/utils_lst.c\
		parsing/dollar.c\
		parsing/clean_tmp_str.c\
		parsing/check_separators.c\
		parsing/lexer_redirection.c\
		parsing/parsing_utils.c\
		parsing/init_tab_cmd.c\
		parsing/fill_tab_cmd.c\
		parsing/fill_tab_redir.c\
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
		exec/pipex.c\
		exec/exec_redirection.c\
		exec/exec_close_fd.c\
		exec/exec_builtin_pipe.c\
		exec/exec_heredoc.c\
		exec/exec_get_path.c\
		free_all.c

DIR_SRC_MINISHELL = ./sources/srcs_minishell/

OBJ	= ${SRCS:.c=.o}

DIR_OBJ = sources/objs/
OBJS = $(addprefix $(DIR_OBJ), $(OBJ))

DEP = ${SRCS:.c=.d}
DEPS = $(addprefix $(DIR_OBJ), $(DEP))

NAME = minishell

HEADERS	= -I includes
CC		= cc
CFLAGS	= -MMD -Wall -Wextra -Werror -g3

${NAME} :	${OBJS}
			@make -C ./sources/libft
			@echo "$(CYAN)Minishell compiled!$(DEF_COLOR)"
			@${CC} ${CFLAGS} ${OBJS} ./sources/libft/libft.a -o ${NAME} -lreadline

all :		minishell

clean:
			@rm -f ${OBJS} ${DEPS}
			@echo "$(BLUE)Minishell cleaned$(DEF_COLOR)"

fclean:		clean
			@make -C ./sources/libft fclean
			@rm -f minishell

re:			fclean all

$(DIR_OBJ)%.o: $(DIR_SRC_MINISHELL)%.c
	@echo "$(BLUE)Compiling: $< $(DEF_COLOR)"
	@${CC} ${CFLAGS} -c $< ${HEADERS} -o $@

-include ${DEPS}

.PHONY: all clean fclean re
