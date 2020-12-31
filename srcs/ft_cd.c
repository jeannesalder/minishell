/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:12:02 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/12/19 09:12:04 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	change_oldpwd(t_var *shell)
{
	int		index;
	char	*oldpwd;
	char	*env;

	index = is_in_env(shell->env, "OLDPWD");
	if (index)
	{
		if (is_in_env(shell->env, "PWD"))
		{
			oldpwd = get_varenv(shell->env, "PWD=");
			env = ft_strjoin("OLDPWD=", oldpwd);
			free(oldpwd);
		}
		else
			env = ft_strdup("OLDPWD");
		modify_env(shell->env, env, index);
		free(env);
	}
}

void	change_pwd(t_var *shell)
{
	int		index;
	char	*pwd;
	char	*env;

	pwd = getcwd(NULL, 0);
	free(shell->pwd);
	shell->pwd = pwd;
	change_oldpwd(shell);
	index = is_in_env(shell->env, "PWD");
	if (index)
	{
		env = ft_strjoin("PWD=", pwd);
		modify_env(shell->env, env, index);
		free(env);
	}
}

char	*check_arg(char **env, char **cmd)
{
	int		nb_args;
	char	*path;

	nb_args = nb_arg(cmd);
	if (nb_args > 1)
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		return (NULL);
	}
	if (!nb_args)
	{
		path = get_varenv(env, "HOME=");
		if (!path)
			ft_putendl_fd("bash: cd: HOME not set", 2);
	}
	else
		path = cmd[1];
	return (path);
}

void	ft_cd(t_var *shell, char **cmd)
{
	char	*path;

	shell->ret = 1;
	path = check_arg(shell->env, cmd);
	if (!path)
		return ;
	if (chdir(path) == -1)
	{
		print_str_fd("bash: cd: ", path, ": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		if (cmd[1] == NULL)
			free(path);
		return ;
	}
	shell->ret = 0;
	if (cmd[1] == NULL)
		free(path);
	change_pwd(shell);
}
