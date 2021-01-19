DIR_SRCS		= ./srcs/

DIR_INCLUDES	= ./includes/

DIR_LIB		= ./libft/

LIBFT		= $(DIR_LIB)libft.a

SRCS		= $(DIR_SRCS)main.c $(DIR_SRCS)ft_cd.c $(DIR_SRCS)cmd_utils.c $(DIR_SRCS)env_utils.c $(DIR_SRCS)exec.c \
			$(DIR_SRCS)ft_pwd.c $(DIR_SRCS)ft_echo.c $(DIR_SRCS)free_utils.c $(DIR_SRCS)ft_export.c $(DIR_SRCS)export_unset_utils.c \
			$(DIR_SRCS)export_utils.c $(DIR_SRCS)ft_unset.c $(DIR_SRCS)ft_env.c $(DIR_SRCS)ft_exit.c $(DIR_SRCS)parsing.c $(DIR_SRCS)utils.c $(DIR_SRCS)tokens.c $(DIR_SRCS)rm.c $(DIR_SRCS)split_semi.c \
			$(DIR_SRCS)value_env.c $(DIR_SRCS)signal.c $(DIR_SRCS)pipes.c $(DIR_SRCS)pipes_utils.c $(DIR_SRCS)redirection.c $(DIR_SRCS)syntax_error.c



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
			$(CC) $(CFLAGS) $(DIR_SRCS)*.o -o $(NAME) $(LIBFT)

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
