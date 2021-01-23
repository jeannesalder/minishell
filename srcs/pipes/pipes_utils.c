/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:17:22 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/22 14:41:05 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_fd(int *pfd, int nb_p)
{
	int	i;

	i = 0;
	while (i < nb_p * 2)
	{
		if (close(pfd[i]))
			exit(EXIT_FAILURE);
		i++;
	}
}

int		next_pipe(char **cmd, int start)
{
	int	end;

	if (!cmd[start])
		return (0);
	end = start;
	while (cmd[end] && cmd[end][0] != '|')
		end++;
	return (end);
}

t_list	*new_lstpipe(char **cmd, int start, int end)
{
	int		i;
	char	**pipe;

	i = 0;
	pipe = ft_calloc(sizeof(*pipe), end - start + 1);
	if (!pipe)
		return (NULL);
	while (start < end)
	{
		pipe[i] = ft_strdup(cmd[start]);
		i++;
		start++;
	}
	return (ft_lstnew(pipe));
}

t_list	*split_pipes(char **cmd)
{
	int		prev;
	int		next;
	t_list	*tmp;
	t_list	*lst_pipe;

	next = -1;
	lst_pipe = NULL;
	while (next && cmd[next])
	{
		prev = next + 1;
		next = next_pipe(cmd, prev);
		tmp = new_lstpipe(cmd, prev, next);
		ft_lstadd_back(&lst_pipe, tmp);
	}
	return (lst_pipe);
}

int		check_pipes(char **cmd)
{
	int	i;
	int	nb_pipes;

	i = 0;
	nb_pipes = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '|' && !cmd[i][1] && cmd[i + 1])
			nb_pipes++;
		i++;
	}
	
	return (nb_pipes);
}
