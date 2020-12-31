/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:35:22 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/12/21 16:35:24 by jgonfroy         ###   ########.fr       */
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

void	modify_env(char **env, char *cmd, int index)
{
	free(env[index]);
	env[index] = remove_quotes(cmd);
}

char	**add_env(char **env, char *cmd)
{
	int		i;
	int		size;
	char	**tab;

	i = 0;
	size = size_env(env);
	tab = ft_calloc(sizeof(char*), size + 2);
	while (i < size)
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	tab[i] = remove_quotes(cmd);
	free_strarray(env);
	return (tab);
}

int	is_in_order(const char *s1, const char *s2)
{
	if (ft_memcmp(s1, s2, ft_strlen(s1) + 1) <= 0)
		return (1);
	return (0);
}
