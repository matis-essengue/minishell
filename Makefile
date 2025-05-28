NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD
LDFLAGS = -L/opt/homebrew/opt/readline/lib
LDLIBS = -lreadline
RM = rm -f

SRCS = \
	src/main.c \
	src/parsing/parser.c \
	src/parsing/tokenizer.c \
	src/parsing/token.c \
	src/parsing/token_checker.c \
	src/utils/stack.c \
	src/parsing/utils.c \
	src/parsing/expander.c \
	src/parsing/quote_remover.c \
	src/parsing/cmd_checker.c
OBJ_DIR = obj
DEP_DIR = $(OBJ_DIR)
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(LIBFT):
	make -C libft

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	$(RM) -r $(OBJ_DIR)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re 