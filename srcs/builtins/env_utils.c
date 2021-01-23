/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:18:06 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/21 21:18:01 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_varenv(char **env, char *name)
{
	int	i;
	int	size;

	size = ft_strlen(name);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, size) == 0)
			return (ft_substr(env[i], size, ft_strlen(env[i]) - size));
		i++;
	}
	return (NULL);
}

char	**cpy_env(char **env)
{
	int		i;
	char	**tab;

	i = 0;
	while (env[i])
		i++;
	tab = ft_calloc(sizeof(char*), i + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (env[i])
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	return (tab);
}

t_env	split_env(char *var)
{
	int		index;
	t_env	dest;

	index = ft_charset('=', var);
	dest.content = 1;
	dest.append = 0;
	if (!index)
	{
		dest.content = 0;
		dest.name = ft_strdup(var);
		dest.value = ft_strdup("");
		return (dest);
	}
	dest.value = ft_substr(var, index, ft_strlen(var) - index);
	if (index > 1 && var[index - 2] == '+')
	{
		dest.append = 1;
		dest.name = ft_substr(var, 0, index - 2);
		return (dest);
	}
	dest.name = ft_substr(var, 0, index - 1);
	return (dest);
}
