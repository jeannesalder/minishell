/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:35:22 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/21 23:18:46 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		nb;
	char	*new;

	i = 0;
	nb = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			nb++;
		i++;
	}
	new = ft_calloc(sizeof(*new), ft_strlen(str) - nb + 1);
	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			new[nb++] = str[i];
		i++;
	}
	return (new);
}

void	modify_env(char **env, char *cmd, int index, t_env var)
{
	char	*dest;

	if (var.append)
		dest = ft_strjoin(env[index], var.value);
	else
		dest = ft_strdup(cmd);
	free(env[index]);
	env[index] = remove_quotes(dest);
	free(dest);
}

char	**add_env(char **env, char *cmd, t_env var)
{
	int		i;
	int		size;
	char	*tmp1;
	char	*tmp2;
	char	**tab;

	i = 0;
	size = size_env(env);
	tab = ft_calloc(sizeof(char*), size + 2);
	while (i < size)
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	if (var.append)
	{
		tmp1 = ft_strjoin(var.name, "=");
		tmp2 = ft_strjoin(tmp1, var.value);
		tab[i] = remove_quotes(tmp2);
		free_multiple(tmp1, tmp2, NULL, NULL);
	}
	else
		tab[i] = remove_quotes(cmd);
	free_strarray(env);
	return (tab);
}

int		is_in_order(const char *s1, const char *s2)
{
	if (ft_memcmp(s1, s2, ft_strlen(s1) + 1) <= 0)
		return (1);
	return (0);
}
