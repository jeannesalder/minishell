/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:17:03 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/22 17:55:31 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*get_envs(char **export, char *env)
{
	int		i;
	int		len;
	char	*tmp;

	env = ft_strjoin(env, "=");
	len = ft_strlen(env);
	i = 0;
	while (export[i] && ft_memcmp(env, export[i], len))
		i++;
	if (export[i])
		tmp = export[i] + len;
	else
		tmp = "\0";
	free(env);
	return (tmp);
}

int		len_env(char *str)
{
	int		i;

	i = 0;
	if (str[i] && str[0] == '{')
		i++;
	if (str[i] && str[i] == '?')
	{
		i++;
		return (i);
	}
	while (str[i] && !(ft_isdigit(str[0]))
		&& (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (ft_isdigit(str[0]))
		i++;
	return (i);
}

int		begin_env(char **str, int i, int brace)
{
	if ((*str)[i + 1] == '{')
		brace = 1;
	return (brace);
}

int		search_env(char **str, t_var *shell, int i, int brace)
{
	char	*temp1;
	char	*temp2;
	char	*env;
	char	*temp3;
	int		len;

	env = 0;
	brace = begin_env(str, i, brace);
	if ((*str)[i + 1 + brace] == '?')
		env = ft_itoa(shell->ret);
	len = len_env(*str + i + 1);
	temp3 = ft_strduplen(*str + i + 1 + brace, len - brace);
	if (!(env))
	{
		env = ft_strdup(get_envs(shell->env, temp3));
		if ((brace == 1 && (*str)[i + 1 + len] != '}'))
		{
			free(env);
			env = ft_strdup("\0");
			brace = 0;
		}
		//if (env[0] == NULL)
		//	ft_putendl_fd("wesh", 2);
	}
	temp1 = ft_strduplen(*str, i);
	temp2 = ft_strdup(*str + i + len + 1 + brace);
	free_multiple(temp3, *str, NULL, NULL);
	temp3 = ft_strjoin(temp1, env);
	*str = ft_strjoin(temp3, temp2);
	len = ft_strlen(env);
	free_multiple(temp1, temp2, env, temp3);
	return (len);
}

int		value_env(t_var *shell, char **str)
{
	int	i;
	int brace;

	i = 0;
	brace = 0;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '\'')
			i = value_env_simpleq(str, i);
		if ((*str)[i] == '"')
			i = value_env_doubleq(str, shell, i, brace);
		if (!(*str)[i])
		{
			ft_putstr_fd("Non finished quotes\n", 2);
			shell->ret = 2;
		}
		if ((*str)[i] == '$' && (*str)[i + 1]
		&& ((*str)[i + 1] == '?' || ft_isalnum((*str)[i + 1])))
			i += search_env(str, shell, i, brace) - 1;
		if ((*str)[i] == '\\' && (*str)[i + 1] && (*str)[i + 1] == ' '
		&& (((*str)[i - 1] && (*str)[i - 1] == ' ') || ((*str)[i + 2]
		&& (*str)[i + 2] == ' ')))
			(*str)[i] = '\n';
		if ((*str)[i] == '\\' && (*str)[i + 1] && (*str)[i + 1] == '"')
                (*str)[i + 1] = '\b';
		if ((*str)[i] == '\\' && (*str)[i + 1] && (*str)[i + 1] == '\'')
                (*str)[i + 1] = '\r';
		if ((*str)[i] == '\\')
			rm_char(str, i);
		i++;
	}
	return (0);
}
