NAME = philo

INPUT = \
	forks.c \
	main.c \
	print.c \
	threads.c \
	utils.c \
	full.c \
	death.c \
	life.c \

OUTPUT = ${INPUT:.c=.o}

all:	${NAME}

.c.o:
	gcc -Wall -Wextra -Werror -pthread -c $< -o ${<:.c=.o}

$(NAME): ${OUTPUT}
	gcc -Wall -Wextra -Werror -pthread ${OUTPUT} -o ${NAME}

clean:
	rm -f ${OUTPUT}

fclean:	clean
	rm -f ${NAME}

re:		fclean all