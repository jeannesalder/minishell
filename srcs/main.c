/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:45:48 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/24 18:47:23 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_read_input(char **env)
{
	int		ret;
	char	c;

	g_read = NULL;
	display(env);
	g_read = ft_calloc(sizeof(char), 1);
	if (!g_read)
		return (NULL);
	g_read[0] = 0;
	ret = read(0, &c, 1);
	if (ret == 0)
	{
		ft_putendl_fd("exit", 2);
		free_and_exit(g_shell, 0, 1);
	}
	while (c != '\n')
	{
		g_read = ft_cat(g_read, c);
		ret = read(0, &c, 1);
	}
	if (ret == -1 || g_read == NULL)
		return (NULL);
	return (g_read);
}

void	display(char **envp)
{
	char	*home;
	char	*path;
	char	cwd[4097];

	home = get_varenv(envp, "HOME");
	if (!home)
		home = ft_strdup("");
	getcwd(cwd, 4096);
	if (!home[0] || ft_strlen(home) >= ft_strlen(cwd))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin("~/", cwd + ft_strlen(home));
	write(2, "\033[1;32mjsaguez&jgonfroy@minishell\033[0;0m", 39);
	write(2, ":", 1);
	write(2, "\033[1;34m", 8);
	ft_putstr_fd(path, 2);
	write(2, "\033[0;0m$", 8);
	write(2, " ", 1);
	free(path);
	free(home);
}

void	init_struct(t_var *shell, t_mini **mini, char **envp)
{
	int	i;

	i = 0;
	ft_bzero(shell, sizeof(t_var));
	g_shell = shell;
	shell->pwd = getcwd(NULL, 0);
	shell->env = cpy_env(envp);
	shell->ret = 0;
	shell->fork = 0;
	while (envp[i] != NULL && shell->path == NULL)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			shell->path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
		i++;
	}
	(*mini) = (t_mini *)malloc(sizeof(t_mini));
	(*mini)->nbtok = 0;
	(*mini)->toks = 0;
	(*mini)->str = 0;
	shell->mini = (*mini);
}

int		main(int ac, char **av, char **envp)
{
	t_var	shell;
	t_mini	*mini;
	int		i;
	int		nbr;

	(void)ac;
	(void)av;
	nbr = 0;
	i = 0;
	init_struct(&shell, &mini, envp);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		mini->str = ft_read_input(shell.env);
		parsing(mini, &shell, i, nbr);
	}
}
