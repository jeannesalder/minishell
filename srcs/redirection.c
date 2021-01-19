/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:46:52 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/19 19:55:15 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

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
		{
			cmd[i] = NULL;
			cmd[i + 1] = NULL;
			i += 2;
		}
		else
		{
			args[j] = ft_strdup(cmd[i]);
			j++;
			i++;
		}
	}
	cmd = NULL;
	cmd = args;
	free_table(args);
	return (cmd);
}

void	redi_in(t_var *shell, char **cmd, int i, int fd)
{
	while (shell->pipe || shell->fork == 0)
	{
		if (shell->fork)
			cmd = (char**)shell->pipe->content;
		else 
			cmd = shell->cmd;
		while (cmd[i])
		{
			fd = 0;
			if (ft_strncmp(cmd[i], "<", 1))
			{
				fd = open(cmd[i + 1], O_RDONLY);
				shell->in = 1;
			}
			if (fd != 0)
				if ((dup2(fd, 0)) == -1)
					if ((close(fd)) == -1)
						shell->ret = 2;
			i++;
		}
		if (shell->fork == 0)
			break;
		shell->pipe = shell->pipe->next;
	}
	return ;
}

void	redi_out(t_var *shell, int i, int fd)
{
	int		ret;
	char	c;
	char	**cmd;

	while (shell->pipe || shell->fork == 0)
	{
		if (shell->fork)
			cmd = (char**)shell->pipe->content;
		else 
			cmd = shell->cmd;
		while (cmd[i])
		{
			fd = 1;
			if (!ft_memcmp(cmd[i], ">", 2))
			{
				fd = open(cmd[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
				shell->out = 1;
			}
			else if (!ft_memcmp(cmd[i], ">>", 3))
			{
				fd = open(cmd[i + 1], O_RDWR | O_CREAT | O_APPEND, 0777);
				ret = 0;
				while ((ret = read(fd, &c, 1)))
					if (ret == -1)
					{
						write(2, "Couldn't read file\n", 19);
						break ;
					}
				shell->out = 1;
			}
			if (fd != 1)
				if ((dup2(fd, 1)) == -1)
					if ((close(fd)) == -1)
						shell->ret = 2;
			i++;
		}
		if (shell->fork == 0)
			break;
		shell->pipe = shell->pipe->next;
	}
	return ;
}

/*void	redi_out(t_var *shell, int i, int fd)
{
	int		ret;
	char	c;
	char	**cmd;
	int		*verif;
	int		j;

	j = 0;
	verif = NULL;
	if (shell->pipe)
		verif = verif_out(shell, verif);
	while (shell->pipe || shell->fork == 0)
	{
		if (shell->fork)
			cmd = (char**)shell->pipe->content;
		else 
			cmd = shell->cmd;
		i = 0;
		while (cmd[i])
		{
			fd = 1;
			if (!ft_memcmp(cmd[i], ">", 2))
			{
				fd = open(cmd[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
				shell->out = 1;
			}
			else if (!ft_memcmp(cmd[i], ">>", 3))
			{
				fd = open(cmd[i + 1], O_RDWR | O_CREAT | O_APPEND, 0777);
				ret = 0;
				while ((ret = read(fd, &c, 1)))
					if (ret == -1)
					{
						write(2, "Couldn't read file\n", 19);
						break ;
					}
				shell->out = 1;
			}
			if (fd != 1 && (shell->fork == 0
			|| verif[j] == 1))
				if ((dup2(fd, 1)) == -1)
					if ((close(fd)) == -1)
						shell->ret = 2;
			i++;
		}
		if (shell->fork == 0)
			break;
		j++;
		shell->pipe = shell->pipe->next;
	}
	free(verif);
	return ;
}*/


char	**redirection(t_var *shell, char **cmd)
{
	int i;
	int fd;

	i = 0;
	fd = 1;
	shell->out = 0;
	shell->in = 0;
	while (cmd[i] && ft_memcmp(cmd[i], ">", 2) && ft_memcmp(cmd[i], ">>", 3))
		i++;
	if (cmd[i])
		redi_out(shell, i, fd);
	fd = 0;
	i = 0;
	while (cmd[i] && ft_strncmp(cmd[i], "<", 1))
		i++;
	if (cmd[i])
		redi_in(shell, cmd, i, fd);
	cmd = delete_redi(shell, cmd);
	return (cmd);
}
