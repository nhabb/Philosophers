# Makefile

NAME = philo

CC = cc
# CFLAGS = -Wall -Wextra -Werror -g

SRC = philo.c routine.c parse_input.c routine_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
