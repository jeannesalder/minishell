/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:22:18 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/12/21 16:22:21 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int		is_in_env(char **env, char *name)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, size) && \
			(!env[i][size] || env[i][size] == '='))
			return (i);
		i++;
	}
	return (0);
}

int		error_id(char *arg)
{
	ft_putstr_fd("bash : export : ", 1);
	ft_putstr_fd(arg, 1);
	ft_putendl_fd(" : not a valid identifier", 1);
	return (0);
}

int		is_valid_id(char *name, char *arg)
{
	int	i;
	int error;

	i = 0;
	error = 0;
	if (name[0] == 0 || (name[0] != '_' && !ft_isalpha(name[0])))
		return (error_id(arg));
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (error_id(arg));
		i++;
	}
	return (1);
}
