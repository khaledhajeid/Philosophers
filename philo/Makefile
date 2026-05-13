NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
SRCS		= main.c \
			  init.c \
			  routine.c \
			  monitor.c \
			  utils.c

OBJS		= $(SRCS:.c=.o)

HEADER		= philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Philosophers compiled successfully!"

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@echo "🧹 Object files cleaned!"

fclean: clean
	rm -f $(NAME)
	@echo "🚿 Executable removed!"

re: fclean all

.PHONY: all clean fclean re