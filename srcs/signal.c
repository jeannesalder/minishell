#include "./../includes/minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	free(g_read);
	g_read = ft_strdup("\0");
	write(1, "\n", 1);
	if (g_shell->fork)
		g_shell->ret = 130;
	else
	{
		g_shell->ret = 1;
		display(g_shell->env);
	}
}

void	sigquit_handler(int signo)
{
	(void)signo;
	if (g_shell->fork)
	{	
		g_shell->ret = 131;
		ft_putendl_fd("Quit (core dumped)", 2);
	}
}
