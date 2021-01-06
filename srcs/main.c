/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:45:48 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/12/18 13:08:31 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_cat(char *input, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (input[i])
		i++;
	str = malloc((i + 2) *sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (input[i])
	{
		str[i] = input[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = 0;
	free(input);
	return (str);
}

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
		free_and_exit(g_shell, 0, 1);
	while (c != '\n')
	{
		g_read = ft_cat(g_read, c);
		ret = read(0, &c, 1);
	}
	if (ret == -1 || g_read == NULL)
		return (NULL);
	return (g_read);
}

void    display(char **envp)
{
        char *home;
        char *path;
        char cwd[4097];

        home = get_varenv(envp, "HOME");
        getcwd(cwd, 4096);
        if (ft_memcmp(cwd, home, ft_strlen(home)))
                path = ft_strdup(cwd);
        else
                path = ft_strjoin("~", cwd + ft_strlen(home));
        write(2, "\033[1;32mminishell@JGONFROY-JSAGUEZ\033[0;0m", 39);
        write(2, ":", 1);
        ft_putstr_fd(path, 2);
        write(2, ": ", 2);
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

int	main(int ac, char **av, char **envp)
{
	t_var	shell;
	t_mini	*mini;

	(void)ac;
	(void)av;
	init_struct(&shell, &mini,  envp);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		mini->str = ft_read_input(shell.env);
		parsing(mini, &shell);
	}
}
