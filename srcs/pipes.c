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


int	next_pipe(char **cmd, int start)
{
	int	end;

	if (!cmd[start])
		return (0);
	end = start;
	while(cmd[end] && cmd[end][0] != '|')
		end++;
	// if (!cmd[end])
	// end--;
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
	// free(cmd);
	return (lst_pipe);
}

int	set_fd_pipe(int *pfd, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		if (pipe(pfd + 2*i) == -1)
			return (EXIT_FAILURE);
		i++;
	}
	return (0);
}

void	close_all(int *pfd, int nb_p)
{
	int i;

	i = 0;
	while (i < nb_p * 2)
	{
		if (close(pfd[i]))
			exit (EXIT_FAILURE);
		i++;
	}
}

void	dup_pipes(int *pfd, int pos, int nb_p)
{
	if (pos != 1)
		dup2(pfd[(2 * pos  - 2)], 0);
	if (pos != nb_p)
		dup2(pfd[2 * pos - 1], 1);
	close_all(pfd, nb_p);
}


void	fork_pipes(t_var *shell, t_list *lst_pipe, int *pfd, int nb_p)
{
	int		pos;
	int		status;
	t_list	*tmp;
	pid_t	child_pid;

	tmp = lst_pipe;
	pos = 1;
	while (tmp)
	{	
		child_pid = fork();
		if (child_pid == -1)
			exit(EXIT_FAILURE);
		if (child_pid == 0)
		{
			shell->cmd = (char **)tmp->content;
			// redirection(shell, shell->cmd);
			dup_pipes(pfd, pos, nb_p);
			if (!(is_a_built(shell, shell->cmd[0])))
				ft_exec(shell);
			exit(0);
		}
		// free_table(tmp->content);
		tmp = tmp->next;
		pos++;
	}
	close_all(pfd, nb_p);
	pos = 0;
	while (pos < 2 * nb_p)
	{
		waitpid(child_pid, &status, 0);
		shell->ret = WEXITSTATUS(status);
		pos++;
	}
}

int	ft_pipes(t_var *shell, int nb_p)
{
	int		*pfd;
	t_list	*lst_pipe;

	//gestion des signaux. Variable fork + signal handler ?
	pfd = ft_calloc(2 * nb_p, sizeof(int));
	if (!pfd)
		return (EXIT_FAILURE);
	if (set_fd_pipe(pfd, nb_p))
		return (EXIT_FAILURE);
	lst_pipe = split_pipes(shell->cmd);
	fork_pipes(shell, lst_pipe, pfd, nb_p);
	return (0);
}