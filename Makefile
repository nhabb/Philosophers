# Makefile

NAME = philo

CC = cc
# CFLAGS = -Wall -Wextra -Werror -g

SRC = philo.c routine.c parse_input.c routine_utils.c handle_mutex.c handle_thread.c init.c parser_utils.c philo_stat.c synchronization.c utils.c philo_check.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
