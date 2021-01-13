/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:19:43 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/12/18 13:26:09 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	error_exec(char *cmd, int error)
{
	print_str_fd("bash: ", cmd, NULL, 2);
	if (error == 14)
	{
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(error), 2);
	return (127);
}

/*
void	exec(t_var *shell, pid_t child_pid, char *path)
{
	int		status;

	if (child_pid == 0)
	{
		if (execve(path, shell->cmd, shell->env) == -1)
			exit(error_exec(shell->cmd[0], errno));
	}
	else
	{
		waitpid(child_pid, &status, 0);
		shell->ret = WEXITSTATUS(status);
		shell->fork = 0;
	}	
}

void	ft_execve(t_var *shell)
{
	char	*path;
	pid_t	child_pid;

	path = ft_strdup("");
	if (shell->path[0])
	{
		free(path);
		path = get_cmd_path(shell->path, shell->cmd[0]);
	}
	child_pid = fork();
	shell->fork = 1;
	if (child_pid < 0)
	{
		shell->ret = 128;
		strerror(errno);
		return ;
	}
	exec(shell, child_pid, path);
	if (path)
		free(path);
}
*/

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
			ret = error_exec(shell->cmd[0], errno);
			if (path)
				free(path);
			exit (ret);
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
	// a supprimer avant de push
	else if (ft_memcmp(cmd, "ret", 4) == 0)
	{	
		ft_putendl_fd(ft_itoa(shell->ret), 1);
		shell->ret = 0;
	}
	else
		return (0);
	return (1);
}

int	ft_exec_cmd(t_var *shell, char **cmd)
{
	int	nb_pipes;

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
		ft_putendl_fd("A renvoyer aux redirections de Juju", 1);
		if (!(is_a_built(shell, cmd[0])))
			fork_for_exec(shell); //est-ce que cette ligne est necessaire ou on peut tout gerer dans les pipes ?
		return (0);
	}
	//Attention actuellement le fonction segfault
	ft_pipes(shell, nb_pipes + 1);
	return (0);
}
