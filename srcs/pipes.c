/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:39:34 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/18 10:31:27 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	set_fd_pipe(int *pfd, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pipe(pfd + 2 * i) == -1)
			return (EXIT_FAILURE);
		i++;
	}
	return (0);
}

void	dup_fd(int *pfd, int pos, int nb_p, int redir)
{
	// ft_putendl_fd(ft_itoa(redir), 2);
	if (pos != 1 && redir != 1 && redir != 3)
		dup2(pfd[(2 * pos - 4)], 0);
	if (pos != nb_p + 1 && redir < 2)
		dup2(pfd[2 * pos - 1], 1);
	close_all_fd(pfd, nb_p);
}

void	end_fork(t_var *shell, int *pfd, int nb_p)
{
	int	i;
	int	status;

	close_all_fd(pfd, nb_p);
	i = 0;
	while (i <= nb_p)
	{
		wait(&status);
		shell->ret = WEXITSTATUS(status);
		i++;
	}
	shell->fork = 0;
}

void	fork_pipes(t_var *shell, t_list *lst_pipe, int *pfd, int nb_p)
{
	int		pos;
	int		redir;
	// t_list	*tmp;
	pid_t	child_pid;

	shell->pipe = lst_pipe;
	pos = 1;
	while (shell->pipe)
	{	
		child_pid = fork();
		shell->fork = 1;
		if (child_pid == -1)
			exit(EXIT_FAILURE);
		if (child_pid == 0)
		{
			shell->cmd = (char **)shell->pipe->content;
			redir = redirection(shell, shell->cmd);
			dup_fd(pfd, pos, nb_p, redir);
			if (!(is_a_built(shell, shell->cmd[0])))
				ft_exec(shell);
		}
		free_table(shell->pipe->content);
		shell->pipe = shell->pipe->next;
		pos++;
	}
	rm_lst(&lst_pipe);
	end_fork(shell, pfd, nb_p);
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
	free(pfd);
	return (0);
}
