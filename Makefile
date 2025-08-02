NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -g3 
LDFLAGS = -L/opt/homebrew/opt/readline/lib
LDLIBS = -lreadline
RM = rm -f

SRCS = \
	src/main.c \
	src/parsing/parser.c \
	src/parsing/tokenizer.c \
	src/parsing/token.c \
	src/parsing/token_checker.c \
	src/parsing/utils.c \
	src/parsing/expander.c \
	src/parsing/quote_remover.c \
	src/parsing/cmd_checker.c \
	src/parsing/tokens_to_cmds.c \
	src/exec/built_in.c\
	src/exec/errors.c\
	src/exec/exec.c\
	src/exec/get_path.c\
	src/exec/manage_files.c\
	src/exec/utils.c\

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