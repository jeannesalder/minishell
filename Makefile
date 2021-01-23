DIR_SRCS		= ./srcs/

DIR_INCLUDES	= ./includes/

DIR_LIB		= ./libft/

LIBFT		= $(DIR_LIB)libft.a

SRCS		= $(DIR_SRCS)main.c $(DIR_SRCS)builtins/ft_cd.c $(DIR_SRCS)exec/cmd_utils.c $(DIR_SRCS)builtins/env_utils.c $(DIR_SRCS)exec/exec.c \
			$(DIR_SRCS)builtins/ft_pwd.c $(DIR_SRCS)builtins/ft_echo.c $(DIR_SRCS)free_utils.c $(DIR_SRCS)builtins/ft_export.c $(DIR_SRCS)builtins/export_unset_utils.c \
			$(DIR_SRCS)builtins/export_utils.c $(DIR_SRCS)builtins/ft_unset.c $(DIR_SRCS)builtins/ft_env.c $(DIR_SRCS)builtins/ft_exit.c $(DIR_SRCS)parsing/parsing.c $(DIR_SRCS)utils.c $(DIR_SRCS)parsing/tokens.c $(DIR_SRCS)rm.c $(DIR_SRCS)parsing/split_semi.c \
			$(DIR_SRCS)parsing/value_env.c $(DIR_SRCS)parsing/value_env_utils.c $(DIR_SRCS)signal.c $(DIR_SRCS)pipes/pipes.c $(DIR_SRCS)pipes/pipes_utils.c $(DIR_SRCS)redirections/redirection.c $(DIR_SRCS)parsing/syntax_error.c $(DIR_SRCS)redirections/verif_redi.c



HEADER		= $(DIR_INCLUDES)

OBJS		= $(SRCS:.c=.o)

INCLUDES	= -I$(HEADER)

NAME		= minishell

CC		= clang
RM		= rm -f
CFLAGS		= -Wall -Werror -Wextra
FSAN		= -g3 -fsanitize=address

$(NAME):	$(OBJS) $(DIR_INCLUDES)*.h
			@make bonus -C $(DIR_LIB)
			@cp $(LIBFT) ./$(NAME)
			$(CC) $(CFLAGS) $(DIR_SRCS)*.o $(DIR_SRCS)builtins/*.o $(DIR_SRCS)exec/*.o $(DIR_SRCS)parsing/*.o $(DIR_SRCS)redirections/*.o $(DIR_SRCS)pipes/*.o -o $(NAME) $(LIBFT)

fsan:		$(OBJS) $(DIR_INCLUDES)*.h
			@make bonus -C $(DIR_LIB)
			@cp $(LIBFT) ./$(NAME)
			$(CC) $(CFLAGS) $(FSAN) $(DIR_SRCS)*.o -o $(NAME) $(LIBFT)

leaks:		$(NAME)
		valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes ./$(NAME)


all:		$(NAME)

clean:
			$(RM) $(OBJS)
			@make clean -C ./libft/

fclean:		clean
			$(RM) $(NAME)
			@make fclean -C ./libft/

re:			fclean all

.PHONY:		all clean fclean re
