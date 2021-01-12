/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:39:34 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/12 15:39:37 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	check_pipes(char **cmd)
{
	int	i;
	int	nb_pipes;

	i = 0;
	nb_pipes = 0;
	if (cmd[0][0] == '|' || cmd[nb_arg(cmd)][0] == '|')
		return (-1);
	while (cmd[i])
	{
		if (cmd[i][0] == '|')
		{
			if (cmd[i+1][0] == '|' || cmd[i-1][0] == '<' || cmd[i-1][0] == '>')
				return (-1);
			nb_pipes++;
		}
		i++;
	}
	return (nb_pipes);
}