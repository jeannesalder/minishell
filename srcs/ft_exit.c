/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 19:23:42 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/21 18:01:39 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	only_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (str[0] != '-')
		if (ft_atoi_llong(str) < 0)
			return (0);
	if (str[0] == '-')
		if (ft_atoi_llong(str) > 0)
			return (0);
	return (1);
}

void	free_and_exit(t_var *shell, int nb_exit)
{
	free(g_read);
	free(shell->pwd);
	free(shell->path);
	free_strarray(shell->env);
	free(shell->mini);
	exit(nb_exit);
}

void	ft_exit(t_var *shell, char **cmd)
{
	int		nb_args;

	shell->ret = 1;
	nb_args = nb_arg(cmd);
	if (nb_args > 1)
	{
		if (!shell->fork)
			ft_putendl_fd("exit", 2);
		ft_putendl_fd("bash: exit: too many arguments", 2);
		return ;
	}
	if (!cmd[1])
		free_and_exit(shell, 0);
	if (!only_digit(cmd[1]))
	{	
		if (!shell->fork)
			ft_putendl_fd("exit", 2);
		print_str_fd("bash: exit: ", cmd[1], ": numeric argument required", 2);
		ft_putchar_fd('\n', 2);
		free_and_exit(shell, 2);
	}
	free_and_exit(shell, ft_atoi_llong(cmd[1]));
}
