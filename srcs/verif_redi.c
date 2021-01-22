/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:17:03 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/22 10:25:40 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	*change_out(int *verif)
{
	int	i;

	i = 0;
	while (verif[i])
		i++;
	i--;
	while (i != -1)
	{
		if (verif[i] == 2)
		{
			while (i != -1)
			{
				verif[i] = 2;
				i--;
			}
			return (verif);
		}
		i--;
	}
	return (verif);
}

int	nb_redi(t_var *shell)
{
	int	i;

	i = 0;
	while (shell->pipe)
	{
		i++;
		shell->pipe = shell->pipe->next;
	}
	return (i);
}

int	*verif_out(t_var *shell, int *verif)
{
	int		i;
	int		j;
	char	**cmd;

	j = 0;
	j = nb_redi(shell);
	verif = ft_calloc(sizeof(int*), j + 1);
	j = 0;
	while (shell->pipe)
	{
		if (shell->fork)
			cmd = (char**)shell->pipe->content;
		i = 0;
		while (cmd[i])
		{
			if (!ft_memcmp(cmd[i], ">", 2) || !ft_memcmp(cmd[i], ">>", 3))
				verif[j] = 1;
			i++;
		}
		if (verif[j] != 1)
			verif[j] = 2;
		j++;
	}
	verif = change_out(verif);
	return (verif);
}

int	drop_redi(char **cmd, int i)
{
	cmd[i] = NULL;
	cmd[i + 1] = NULL;
	i += 2;
	return (i);
}

int	open_redi(t_var *shell, char **cmd, int i, int fd)
{
	fd = open(cmd[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	shell->out = 1;
	return (fd);
}
