NAME = philo

INPUT = \
	philo/forks.c \
	philo/main.c \
	philo/print.c \
	philo/threads.c \
	philo/utils.c \

OUTPUT = ${INPUT:.c=.o}

BINPUT = \

BOUTPUT = ${BINPUT:.c=.o}

all:	${NAME}

.c.o:
	gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

$(NAME): ${INPUT}
	gcc -Wall -Wextra -Werror ${INPUT} -o ${NAME}

bonus: ${BINPUT}
	gcc -Wall -Wextra -Werror ${BINPUT} -o ${NAME}

clean:
	rm -f ${OUTPUT} ${BOUTPUT}

fclean:	clean
	rm -f ${NAME}

re:		fclean all