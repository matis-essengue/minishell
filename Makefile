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
	src/parsing/redirect_utils.c \
	src/parsing/tokens_to_cmds_utils.c \
	src/parsing/cleaner.c \
	src/exec/parent_process.c \
	src/exec/child_process.c \
	src/exec/get_path.c \
	src/exec/manage_files.c \
	src/exec/utils.c \
	src/exec/errors.c \
	src/exec/init_struct_env.c \
	src/exec/term_state.c \
	src/built-in/built_in.c \
	src/built-in/cd.c \
	src/built-in/echo.c \
	src/built-in/env.c \
	src/built-in/exit.c \
	src/built-in/export.c \
	src/built-in/pwd.c \
	src/built-in/unset.c \
	src/built-in/built_in_utils.c \
	src/built-in/export_utils.c \

	
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