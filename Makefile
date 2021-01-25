NAME	= minishell

CC	= clang
CFLAGS	= -Wall -Wextra -Werror
FSAN	= -g3 -fsanitize=address
RM	= rm -f

DIR_SRCS	= srcs

SRCS 	= $(DIR_SRCS)/main.c $(DIR_SRCS)/free_utils.c $(DIR_SRCS)/rm.c $(DIR_SRCS)/signal.c \
	$(DIR_SRCS)/builtins/env_utils.c $(DIR_SRCS)/builtins/export_utils.c $(DIR_SRCS)/builtins/ft_echo.c \
	$(DIR_SRCS)/builtins/ft_exit.c $(DIR_SRCS)/builtins/ft_pwd.c $(DIR_SRCS)/builtins/export_unset_utils.c \
	$(DIR_SRCS)/builtins/ft_cd.c $(DIR_SRCS)/builtins/ft_env.c $(DIR_SRCS)/builtins/ft_export.c \
	$(DIR_SRCS)/builtins/ft_unset.c \
	$(DIR_SRCS)/exec/cmd_utils.c $(DIR_SRCS)/exec/exec.c \
	$(DIR_SRCS)/parsing/parsing.c $(DIR_SRCS)/parsing/split_semi.c $(DIR_SRCS)/parsing/syntax_error.c \
	$(DIR_SRCS)/parsing/tokens.c $(DIR_SRCS)/parsing/utils.c $(DIR_SRCS)/parsing/value_env.c \
	$(DIR_SRCS)/parsing/value_env_utils.c \
	$(DIR_SRCS)/pipes/pipes.c $(DIR_SRCS)/pipes/pipes_utils.c \
	$(DIR_SRCS)/redirections/redirection.c $(DIR_SRCS)/redirections/verif_redi.c

OBJS = ${SRCS:.c=.o}

HEADER = -I ./includes/

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJS)
	make bonus -C libft
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -L. libft/libft.a

fsan:	$(OBJS)
	make bonus -C libft
	$(CC) $(CFLAGS) $(FSAN) $(SRCS) -o $(NAME) -L. libft/libft.a

leaks:	$(NAME)
	valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes ./$(NAME)

all:	$(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re fsan leaks
