/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:18:33 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/12/19 09:19:18 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	ft_echo(t_var *shell, char **cmd)
{
	int i;
	int arg;

	shell->ret = 0;
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
}
