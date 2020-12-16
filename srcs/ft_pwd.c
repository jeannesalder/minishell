#include "./../includes/minishell.h"

int ft_pwd(t_var *shell)
{
	ft_putendl_fd(shell->pwd, 1);
	return (0);
}