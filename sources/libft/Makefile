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

SRC    = 	ft_strlen.c\
			ft_atoi.c\
			ft_bzero.c\
			ft_calloc.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_strchr.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strncpy.c\
			ft_strncmp.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_strdup.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_split.c\
			ft_itoa.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c\
			ft_str_is_numeric.c\
			get_next_line.c\
			get_next_line_utils.c

DIR_SRC = ./src/
DIR_OBJ = ./obj/

DEP	= ${SRC:.c=.d}

DEPS = $(addprefix $(DIR_OBJ), $(DEP))

SRCS = $(addprefix $(DIR_SRC), $(SRC))
OBJ	= ${SRC:.c=.o}
OBJS = $(addprefix $(DIR_OBJ), $(OBJ))

HEADERS	= -I ./includes
CC		= gcc
CFLAGS	= -MMD -Wall -Wextra -Werror
NAME	= libft.a

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
				@echo "$(GREEN)Compiling: $< $(DEF_COLOR)"
				@$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	${OBJS} 
			@ar -rc ${NAME} ${OBJS}
			@echo "$(GREEN)libft compiled!$(DEF_COLOR)"

all :		${NAME}

clean:
			@rm -f ${OBJS} ${DEPS} 

fclean:		clean
			@rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re

-include ${DEPS}
