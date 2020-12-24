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

char	*get_cmd_path(char *path, char *cmd)
{
	int			i;
	char		*tmp;
	char		*cmd_path;
	char		**path_split;
	struct stat	file;

	i = 0;
	if (ft_charset('/', cmd))
		return (ft_strdup(cmd));
	path_split = NULL;
	path_split = ft_split(path, ':');
	while (path_split[i] != NULL)
	{
		tmp = ft_strjoin(path_split[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (stat(cmd_path, &file) == 0)
		{
			free_strarray(path_split);
			return (cmd_path);
		}
		i++;
		free(cmd_path);
	}
	free_strarray(path_split);
	return (NULL);
}

int		error_exec(char *cmd, int error)
{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(cmd, 1);
		if (error == 14)
		{
			ft_putendl_fd(": command not found", 1);
			return (127);
		}
		ft_putstr_fd(": ", 1);
		ft_putendl_fd(strerror(errno), 1);
		return (127);
}

int		ft_execve(t_var *shell)
{
	char	*path;
	pid_t	child_pid;
	int		wstatus;

	path = ft_strdup("");
	if (shell->path[0])
	{
		free(path);
		path = get_cmd_path(shell->path, shell->cmd[0]);
	}
	child_pid = fork();
	if (child_pid < 0)
		return (-1);
	else if (child_pid == 0)
	{
		shell->ret = 0;
		if (execve(path, shell->cmd, shell->env) == -1)
			shell->ret = error_exec(shell->cmd[0], errno);
		exit(shell->ret);
	}
	else
	{
		waitpid(child_pid, &wstatus, 0);
		shell->ret = WEXITSTATUS(wstatus);
	}
	if (path)
		free(path);
	return (1);
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

int		ft_exec_cmd(t_var *shell)
{
	if (!(is_a_built(shell, shell->cmd[0])))
		ft_execve(shell);
	return (1); // ret a changer;
}
