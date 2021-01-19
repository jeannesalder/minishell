/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:19:43 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/19 17:44:10 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	find_cmd(char *path, char *cmd)
{
	struct stat	file;

	stat(path, &file);
	if ((file.st_mode & S_IFREG) && (file.st_mode & S_IXUSR))
		return (0);
	if (file.st_mode & S_IFREG)
	{
		print_str_fd("bash: ", cmd, ": permission denied\n", 2);
		return (126);
	}
	print_str_fd("bash: ", cmd, " : command not found\n", 2);
	return (127);
}

void	ft_exec(t_var *shell)
{
	char	*path;

	path = ft_strdup("");
	if (shell->path[0])
	{
		free(path);
		path = get_cmd_path(shell->path, shell->cmd[0]);
	}
	shell->ret = find_cmd(path, shell->cmd[0]);
	if (shell->ret)
	{
		if (path)
			free(path);	
		exit (shell->ret);
	}
	execve(path, shell->cmd, shell->env);
	if (path)
		free(path);
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
	int	cp_out;
	int	cp_in;

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
		cp_out = dup(1);
		cp_in = dup(0);
		cmd = redirection(shell, cmd);	
		if (!(is_a_built(shell, cmd[0])))
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
