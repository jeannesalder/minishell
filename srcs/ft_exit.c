/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 19:23:42 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/12/22 19:23:45 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	only_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '_' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (ft_strlen(str) > 17)
		return (0);
	return (1);
}

void	free_and_exit(t_var *shell, int nb_exit)
{
	free(shell->pwd);
	free(shell->path);
	free_strarray(shell->env);
	free_strarray(shell->cmd);
	free_strarray(shell->mini->cmds);
	free(shell->mini);
	free(g_read);
	exit(nb_exit);
}

void	ft_exit(t_var *shell, char **cmd)
{
	int		nb_args;

	shell->ret = 1;
	nb_args = nb_arg(cmd);
	ft_putendl_fd("exit", 1);
	if (nb_args > 1)
	{
		ft_putendl_fd("bash: exit: too many arguments", 2);
		return ;
	}
	if (!cmd[1])
		free_and_exit(shell, 0);
	if (!only_digit(cmd[1]))
	{
		print_str_fd("bash: exit: ", cmd[1], ": numeric argument required", 2);
		ft_putchar_fd('\n', 2);
		free_and_exit(shell, 2);
	}
	free_and_exit(shell, ft_atoi(cmd[1]));
}
