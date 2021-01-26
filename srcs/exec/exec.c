/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:21:19 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/26 11:21:38 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		error_exec(char *cmd)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*error;

	tmp1 = ft_strjoin("bash: ", cmd);
	tmp2 = ft_strjoin(tmp1, ": ");
	if (errno == 14)
		tmp3 = ft_strjoin(tmp2, "command not found");
	else
		tmp3 = ft_strjoin(tmp2, strerror(errno));
	error = ft_strjoin(tmp3, "\n");
	write(2, error, ft_strlen(error));
	free_multiple(tmp1, tmp2, tmp3, error);
	if (errno == EACCES)
		return (126);
	return (127);
}

void	ft_exec(t_var *shell)
{
	int		ret;
	char	*path;

	if (shell->path[0])
		path = get_cmd_path(shell->path, shell->cmd[0]);
	else
		path = ft_strdup(shell->cmd[0]);
	if (execve(path, shell->cmd, shell->env) == -1)
	{
		ret = error_exec(shell->cmd[0]);
		free(path);
		exit(ret);
	}
}

void	fork_for_exec(t_var *shell)
{
	int		status;
	pid_t	child_pid;

	child_pid = fork();
	shell->fork = 1;
	if (child_pid < 0)
	{
		shell->ret = 128;
		strerror(errno);
		return ;
	}
	if (child_pid == 0)
		ft_exec(shell);
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFSIGNALED(status))
			shell->ret = 128 + WTERMSIG(status);
		else
			shell->ret = WEXITSTATUS(status);
		if (shell->ret == 131)
			ft_putendl_fd("Quit (core dumped)", 2);
		shell->fork = 0;
	}
}

int		is_a_built(t_var *shell, char *cmd)
{
	if (ft_memcmp(cmd, "echo", 5) == 0)
		ft_echo(shell, shell->cmd);
	else if (ft_memcmp(cmd, "cd", 3) == 0)
		ft_cd(shell, shell->cmd);
	else if (ft_memcmp(cmd, "pwd", 4) == 0)
		ft_pwd(shell);
	else if (ft_memcmp(cmd, "export", 7) == 0)
		ft_export(shell, shell->env, shell->cmd);
	else if (ft_memcmp(cmd, "unset", 5) == 0)
		ft_unset(shell, shell->cmd);
	else if (ft_memcmp(cmd, "env", 4) == 0)
		ft_env(shell, shell->env);
	else if (ft_memcmp(cmd, "exit", 5) == 0)
		ft_exit(shell, shell->cmd);
	else
		return (0);
	return (1);
}

int		ft_exec_cmd(t_var *shell, char **cmd)
{
	int	nb_pipes;
	int	ret;
	int	cp_out;
	int	cp_in;

	nb_pipes = check_pipes(cmd);
	if (!nb_pipes)
	{
		cp_out = dup(1);
		cp_in = dup(0);
		redirection(shell, cmd, 0);
		if (shell->cmd[0] && !(is_a_built(shell, shell->cmd[0])))
			fork_for_exec(shell);
		dup2(cp_out, 1);
		dup2(cp_in, 0);
		close(cp_out);
		close(cp_in);
		return (0);
	}
	ret = ft_pipes(shell, nb_pipes);
	if (ret)
		shell->ret = ret;
	return (0);
}
