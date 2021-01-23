/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:38:45 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/22 21:17:48 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**sort_env(char **cpy)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (cpy[i + 1])
	{
		j = i + 1;
		while (cpy[j])
		{
			if (!(is_in_order(cpy[i], cpy[j])))
			{
				tmp = cpy[i];
				cpy[i] = cpy[j];
				cpy[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (cpy);
}

void	print_env(char **env)
{
	int		i;
	t_env	tmp;

	i = 0;
	while (env[i])
	{
		tmp = split_env(env[i]);
		if (ft_strncmp(tmp.name, "_", 2) != 0)
		{
			print_str_fd("declare -x ", tmp.name, NULL, 1);
			if (tmp.content == 1)
				print_str_fd("=\"", tmp.value, "\"", 1);
			ft_putchar_fd('\n', 1);
		}
		free(tmp.name);
		free(tmp.value);
		i++;
	}
	free_table(env);
}

void	change_path(t_var *shell, t_env tmp)
{
	if (strncmp(tmp.name, "PATH", 4) == 0 && tmp.content)
	{
		free(shell->path);
		shell->path = tmp.value;
		if (!tmp.value[0])
			shell->path = ft_strdup("\0");
	}
}

int		no_arg(char **env, char *cmd)
{
	if (!cmd)
	{
		print_env(sort_env(cpy_env(env)));
		return (1);
	}
	return (0);
}

void	ft_export(t_var *shell, char **env, char **cmd)
{
	int		i;
	int		index;
	t_env	tmp;

	shell->ret = 0;
	if (no_arg(env, cmd[1]))
		return ;
	i = 1;
	while (cmd[i])
	{
		tmp = split_env(cmd[i]);
		if ((is_valid_id(shell, tmp.name, cmd[i])))
		{
			index = is_in_env(shell->env, tmp.name);
			if (index && tmp.content == 1)
				modify_env(shell->env, cmd[i], index, tmp);
			if (index == 0)
				shell->env = add_env(shell->env, cmd[i], tmp);
			change_path(shell, tmp);
		}
		free_multiple(tmp.name, tmp.value, NULL, NULL);
		i++;
	}
}
