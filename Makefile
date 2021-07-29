SRCS	= ./srcs/solver.c ./srcs/main.c ./srcs/initialize.c ./srcs/parse_map.c ./srcs/parse_more.c 

INCS	= includes
OBJS	= ${SRCS:.c=.o}

NAME	= bsq

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

.c.o:
			${CC} -I${INCL} ${CFLAGS} -c $< -o ${<:.c=.o}


${NAME}: 	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		fclean clean all re
