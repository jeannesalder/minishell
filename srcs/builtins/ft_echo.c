/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:18:33 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/26 11:01:08 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_arg(char *cmd)
{
	int	i;

	if (cmd[0] != '-')
		return (0);
	i = 1;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_var *shell, char **cmd)
{
	int	i;
	int	arg;

	shell->ret = 0;
	i = 1;
	arg = 0;
	ft_putendl_fd(cmd[0], 2);
	ft_putendl_fd(cmd[1], 2);
	while (cmd[i] != NULL && is_arg(cmd[i]))
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
}
