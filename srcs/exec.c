/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:19:43 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/18 10:46:44 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	error_exec(char *cmd)
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
	return (127);
}

void	ft_exec(t_var *shell)
{
	int		ret;
	char	*path;

	path = ft_strdup("");
	if (shell->path[0])
	{
		free(path);
		path = get_cmd_path(shell->path, shell->cmd[0]);
	}
	if (execve(path, shell->cmd, shell->env) == -1)
	{
		ret = error_exec(shell->cmd[0]);
		if (path)
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
		shell->ret = WEXITSTATUS(status);
		shell->fork = 0;
	}
}

int	is_a_built(t_var *shell, char *cmd)
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

int	ft_exec_cmd(t_var *shell, char **cmd)
{
	int	nb_pipes;
	int	ret;
	int stdout;
	int	stdin;

	nb_pipes = check_pipes(cmd);
	if (nb_pipes == -1)
	{
		ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
		shell->ret = 2;
		return (1);
	}
	if (cmd[nb_arg(cmd)][0] == '<' || cmd[nb_arg(cmd)][0] == '>')
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
		shell->ret = 2;
		return (1);
	}
	if (!nb_pipes)
	{
		stdout = dup(1);
		stdin = dup(0);
		redirection(shell, cmd);	
		if (!(is_a_built(shell, cmd[0])))
			fork_for_exec(shell);
		dup2(stdout, 1);
		dup2(stdin, 0);
		close(stdout);
		close(stdin);
		return (0);
	}
	ret = ft_pipes(shell, nb_pipes);
	if (ret)
		shell->ret = ret;
	return (0);
}
