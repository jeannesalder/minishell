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

int	next_pipe(char **cmd, int start)
{
	int	end;

	if (!cmd[start])
		return (0);
	end = start;
	while(cmd[end] && cmd[end][0] != '|')
		end++;
	return (end);
}

t_list	*new_lstpipe(char **cmd, int start, int end)
{
	int		i;
	char	**pipe;

	i = 0;
	pipe = ft_calloc(sizeof(char), start - end + 1);
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
	t_list	**lst_pipe;

	prev = -1;
	next = -1;
	lst_pipe = NULL;
	// *lst_pipe = NULL;
	while (next)
	{
		prev = next + 1;
		next = next_pipe(cmd, prev);
		if (!next)
			break;
		next = 0;
		tmp = new_lstpipe(cmd, next, prev);
		ft_lstadd_back(lst_pipe, tmp);	
	}
	return (*lst_pipe);
}


void	ft_pipes(t_var *shell, int nb_p)
{
	int		*pfd;
	t_list	*lst_pipe;

	lst_pipe = split_pipes(shell->cmd);
	pfd = ft_calloc(2 * nb_p, sizeof(int));
	if (!pfd)
		return ;
	// do_pipes(pfd, nb_p);

}