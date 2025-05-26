NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRCS = src/main.c src/parsing/parser.c
OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME) 
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re 