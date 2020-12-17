#include "./../includes/minishell.h"

int	ft_echo(t_var *shell, char **cmd)
{
	int i;
	int arg;
	(void)shell;
	
	i = 1;
	arg = 0;
	while (cmd[i] != NULL && !ft_memcmp(cmd[i], "-n", 3))
	{
		arg = 1;
		i++;
	}
	while (cmd[i] != NULL)
	{
		ft_putstr_fd(cmd[i], 1);
		i++;
		if (cmd[i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (!arg)
		ft_putchar_fd('\n', 1);
	return (1);
}