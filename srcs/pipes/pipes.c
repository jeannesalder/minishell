/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:39:34 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/26 16:15:23 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end_fork(t_var *shell, int *pfd, int nb_p, pid_t child_pid)
{
	int	i;
	int	status;

	i = 0;
	close_all_fd(pfd, nb_p);
	waitpid(child_pid, &status, 0);
	if (WIFSIGNALED(status))
		shell->ret = 128 + WTERMSIG(status);
	else
		shell->ret = WEXITSTATUS(status);
	while (i <= nb_p - 1)
	{
		wait(&status);
		i++;
	}
	shell->fork = 0;
}

void	fork_pipes(t_var *shell, t_list *lst_pipe, int *pfd, int nb_p)
{
	int		pos;
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
			dup_fd(shell, pfd, pos, nb_p);
			shell->redi = redirection(shell, shell->cmd);
			if (!(is_a_built(shell, shell->cmd[0])))
				ft_exec(shell);
		}
		shell->pipe = get_next_pipe(shell->pipe, shell->redi);
		pos++;
	}
	rm_lst(&lst_pipe);
	end_fork(shell, pfd, nb_p, child_pid);
}

int		ft_pipes(t_var *shell, int nb_p)
{
	int		*pfd;
	t_list	*lst_pipe;

	pfd = ft_calloc(2 * nb_p, sizeof(int));
	if (!pfd)
	{
		ft_putendl_fd("bash error : no more memory available\nexit", 2);
		free_and_exit(shell, EXIT_FAILURE, 0);
	}
	if (set_fd_pipe(pfd, nb_p))
	{
		ft_putendl_fd("bash error : too much pipes\nexit", 2);
		free(pfd);
		free_and_exit(shell, EXIT_FAILURE, 0);
	}
	lst_pipe = split_pipes(shell->cmd);
	fork_pipes(shell, lst_pipe, pfd, nb_p);
	free(pfd);
	return (0);
}
