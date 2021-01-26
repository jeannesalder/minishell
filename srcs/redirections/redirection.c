/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:46:52 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/26 16:32:25 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		count_redi(t_var *shell, char **cmd)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < shell->mini->nbtok && cmd[i])
	{
		if (!ft_memcmp(cmd[i], ">", 2) || !ft_memcmp(cmd[i], ">>", 3)
		|| !ft_memcmp(cmd[i], "<", 2))
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

char	**delete_redi(t_var *shell, char **cmd)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	shell->mini->nbtok -= count_redi(shell, cmd) * 2;
	args = (char **)ft_calloc(sizeof(char*), shell->mini->nbtok + 1);
	while (cmd[i])
	{
		if (!ft_memcmp(cmd[i], ">", 2) || !ft_memcmp(cmd[i], ">>", 3)
		|| !ft_memcmp(cmd[i], "<", 2))
			i = drop_redi(cmd, i);
		else
		{
			args[j] = ft_strdup(cmd[i]);
			ft_bzero(cmd[i], ft_strlen(cmd[i]));
			j++;
			i++;
		}
	}
	free_table(shell->cmd);
	cmd = NULL;
	return (args);
}

void	redi_in(t_var *shell, char **cmd, int i, int fd)
{
	while (cmd[i])
	{
		fd = 0;
		if (!ft_memcmp(cmd[i], "<", 2))
		{
			fd = open(cmd[i + 1], O_RDONLY);
			shell->in = 1;
			if (fd == -1)
				shell->in = -1;
		}
		if (fd != 0 && fd != -1)
			if ((dup2(fd, 0)) == -1)
				if ((close(fd)) == -1)
					shell->ret = 2;
		i++;
	}
	return ;
}

void	redi_out(t_var *shell, char **cmd, int i, int fd)
{
	int		ret;
	char	c;

	while (cmd[i])
	{
		fd = 1;
		if (!ft_memcmp(cmd[i], ">", 2))
			fd = open_redi(shell, cmd, i, fd);
		else if (!ft_memcmp(cmd[i], ">>", 3))
		{
			fd = open(cmd[i + 1], O_RDWR | O_CREAT | O_APPEND, 0777);
			ret = 0;
			while ((ret = read(fd, &c, 1)) && ret > 0)
				if (ret == -1)
					write(2, "Couldn't read file\n", 19);
			if (ret == -1)
				break ;
			shell->out = 1;
		}
		if (fd != 1)
			if ((dup2(fd, 1)) == -1)
				if ((close(fd)) == -1)
					shell->ret = 2;
		i++;
	}
}

int		redirection(t_var *shell, char **cmd)
{
	int i;
	int	j;
	int fd;

	i = 0;
	j = 0;
	shell->out = 0;
	shell->in = 0;
	while (cmd[i] && ft_memcmp(cmd[i], ">", 2) && ft_memcmp(cmd[i], ">>", 3))
		i++;
	fd = 1;
	if (cmd[i])
		redi_out(shell, cmd, i, fd);
	while (cmd[j] && ft_strncmp(cmd[j], "<", 1))
		j++;
	fd = 0;
	if (cmd[j])
		redi_in(shell, cmd, j, fd);
	if ((cmd[i] || cmd[j]) && shell->in != -1)
	{
		shell->cmd = delete_redi(shell, cmd);
		return (1);
	}
	return (0);
}
