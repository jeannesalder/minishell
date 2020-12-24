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
	if (!(str = malloc((i + 2) * sizeof(char))))
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
	write(1, "> ", 2);
	if (!(input = ft_calloc(sizeof(char), 1)))
		return (NULL);
	input[0] = 0;
	ret = read(0, &c, 1);
	if (ret == 0)
	{
		write(1, "\n", 1);
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

int		init_var(t_var *shell, char **envp)
{
	int i;

	i = 0;
	ft_bzero(shell, sizeof(t_var));
	shell->pwd = getcwd(NULL, 0);
	shell->env = cpy_env(envp);
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
	write(1, "En construction...", 18);
	//reset shell : free input et ft_read ?
}

int		main(int ac, char **av, char **envp)
{
	char	*input;
	t_var	shell;

	(void)ac;
	(void)av;
	init_var(&shell, envp);
	signal(SIGINT, sigint_handler);
	while (1)
	{
		input = ft_read_input(); //segfault dans le cas d'un retour a la ligne seul
		shell.cmd = ft_split(input, ' ');
		free(input);
		ft_exec_cmd(&shell);
		free_strarray(shell.cmd);
	}
	// Inutile ici non ?
	// free(shell.pwd);
	// free(shell.path);
	// free_strarray(shell.env);
}
