/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:39:22 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/20 22:06:17 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else
	{
		free(g_read);
		g_read = NULL;
	}
}
