NAME	=	philo

HEAD	=	philosophers.h

CFLAGS	=	-Wall -Wextra -Werror

CC		=	gcc

SRCS	=	main.c\
			checker.c\
			utils.c\
			life.c

OBJS 	= $(SRCS:%.c=%.o)

$(NAME): $(OBJS) $(HEAD)
	@$(CC) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re