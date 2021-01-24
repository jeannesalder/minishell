NAME	= minishell

CC	= clang
CFLAGS	= -Wall -Wextra -Werror
FSAN	= -g3 -fsanitize=address
RM	= rm -f

SRCS 	= srcs/main.c srcs/free_utils.c srcs/rm.c srcs/signal.c \
	srcs/builtins/env_utils.c srcs/builtins/export_utils.c srcs/builtins/ft_echo.c \
	srcs/builtins/ft_exit.c srcs/builtins/ft_pwd.c srcs/builtins/export_unset_utils.c \
	srcs/builtins/ft_cd.c srcs/builtins/ft_env.c srcs/builtins/ft_export.c srcs/builtins/ft_unset.c \
	srcs/exec/cmd_utils.c srcs/exec/exec.c \
	srcs/parsing/parsing.c srcs/parsing/split_semi.c srcs/parsing/syntax_error.c srcs/parsing/tokens.c\
	srcs/parsing/utils.c srcs/parsing/value_env.c srcs/parsing/value_env_utils.c \
	srcs/pipes/pipes.c srcs/pipes/pipes_utils.c \
	srcs/redirections/redirection.c srcs/redirections/verif_redi.c

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
