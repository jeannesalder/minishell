/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:53:26 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/12/22 13:53:28 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_env(t_var *shell, char **env)
{
	int		i;
	t_env	tmp;

	(void)shell;
	i = 0;
	while (env[i])
	{
		tmp = split_env(env[i]);
		if (tmp.content)
		{
			ft_putstr_fd(tmp.name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(tmp.value, 1);
		}
		// ft_printf("%s=%s\n", tmp.name, tmp.value);
		i++;
		free(tmp.name);
		free(tmp.value);
	}
	return (0);
}
