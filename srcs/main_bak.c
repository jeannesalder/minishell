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

char	*ft_read_input(void)
{
	int		ret;
	char	c;
	char	*input;

	input = NULL;
	write(1, "$ ", 2);
	input = ft_calloc(sizeof(char), 1);
	if (!input)
		return (NULL);
	input[0] = 0;
	ret = read(0, &c, 1);
	if (ret == 0)
	{
		write(1, "exit\n", 5);
		//free tout ce qu'il y a à free (dans main ? => break la boucle ?)
		exit(0);
	}
	while (c != '\n')
	{
		input = ft_cat(input, c);
		ret = read(0, &c, 1);
	}
	if (ret == -1 || input == NULL)
		return (NULL);
	return (input);
}

int	init_var(t_var *shell, char **envp)
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
	return (1);
}

void	sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	if (g_shell->fork)
		g_shell->ret = 130;
		
	else
	{
		g_shell->ret = 1;
		write(1, "$ ", 2);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_var	shell;

	(void)ac;
	(void)av;
	init_var(&shell, envp);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		input = ft_read_input();
		shell.cmd = ft_split(input, ' ');
		free(input);
		ft_exec_cmd(&shell);
		free_strarray(shell.cmd);
	}
}
