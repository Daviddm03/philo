#COLORS
CYAN 	= \033[1;36m
GREEN   = \033[32m

#FILES
NAME = philo
SRCS = 	srcs/eating.c srcs/error_handler.c srcs/init.c srcs/input.c \
		srcs/main.c	srcs/only_one.c srcs/threads.c srcs/utils.c srcs/utils2.c
OBJS = $(SRCS:.c=.o)

#FLAGS
CC = cc
CFLAGS = -fsanitize=thread -Wall -Wextra -Werror -g

#COMMANDS
RM = rm -rf

#RULES
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(CYAN)----> COMPILATION IS DONE! 🫡 <----"

srcs/%.o: srcs/%.c
	@$(CC) $(CFLAGS) -c $< -o $@


clean: 
	@$(RM) $(OBJS)
	@echo "$(CYAN)----> OBJS CLEANED 👌 <----"

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re