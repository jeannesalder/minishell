DIR_SRCS		= ./srcs/

DIR_INCLUDES	= ./includes/

DIR_LIB		= ./libft/

LIBFT		= $(DIR_LIB)libft.a
SRCS		= $(DIR_SRCS)main.c $(DIR_SRCS)builtin.c $(DIR_SRCS)list_utils.c $(DIR_SRCS)env_utils.c $(DIR_SRCS)exec.c


HEADER		= $(DIR_INCLUDES)

OBJS		= $(SRCS:.c=.o)

INCLUDES	= -I$(HEADER)

NAME		= minishell

CC			= clang 
RM			= rm -f
CFLAGS			= -Wall -Werror -Wextra

$(NAME):		$(OBJS) $(DIR_INCLUDES)*.h
			@make bonus -C $(DIR_LIB)
			@cp $(LIBFT) ./$(NAME)
			$(CC) $(CFLAGS) $(DIR_SRCS)*.o -o $(NAME) $(LIBFT)


all:		$(NAME)

clean:
			$(RM) $(OBJS)
			@make clean -C ./libft/

fclean:		clean
			$(RM) $(NAME)
			@make fclean -C ./libft/

re:			fclean all

.PHONY:		all clean fclean re
