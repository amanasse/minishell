SRCS    = 	ft_strlen.c\
			ft_char.c\
			count_nb.c\
			count_hexa.c\
			ft_putchar.c\
			ft_putnbr_base_x_x.c\
			ft_printf.c\
			ft_putnbr_base.c\
			ft_putnbr_d_i.c\
			ft_putnbr_u.c\
			ft_string.c\
			count_u.c\
			count_hexa_x_x.c

OBJS	= ${SRCS:.c=.o}
HEADERS	= "ft_printf.h"
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
NAME	= libftprintf.a

.c.o:
	${CC} ${CFLAGS} -c $< -I includes -o ${<:.c=.o}

${NAME}:	${OBJS} 
			ar -rc ${NAME} ${OBJS} 

all :		${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re
