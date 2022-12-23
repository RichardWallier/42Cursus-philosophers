SOURCES	=	main.c utils.c routine.c thread.c

OBJECTS	=	$(SOURCES:.c=.o)

NAME	=	philosophers

CFLAGS	=	-Wall -Werror -Wextra -g

PTHREAD_FLAGS = -pthread

CC	=	gcc

RM	=	rm -f

.c.o:
	$(CC) $(PTHREAD_FLAGS) $(CFLAGS) -c $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJECTS)
	$(CC) $(PTHREAD_FLAGS) $(OBJECTS) -o $(NAME)

clean:	
	$(RM) $(OBJECTS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
