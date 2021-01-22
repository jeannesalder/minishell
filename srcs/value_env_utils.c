/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:41:56 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/22 14:03:55 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int		value_env_simpleq(char **str, t_var *shell, int i, int brace)
{
	i++;
	while ((*str)[i] && ((*str)[i] != '\''))
	{
		if ((*str)[i] == '$' && (*str)[i + 1]
		&& ft_isalnum((*str)[i + 1]))
			i += search_env(str, shell, i, brace) - 1;
		i++;
	}
	return (i);
}

int		value_env_doubleq(char **str, t_var *shell, int i, int brace)
{
	i++;
	while ((*str)[i] && ((*str)[i] != '"'))
	{
		if ((*str)[i] == '$' && (*str)[i + 1]
		&& ft_isalnum((*str)[i + 1]))
			i += search_env(str, shell, i, brace) - 1;
		if ((*str)[i] == '\\' && ((*str)[i + 1] == '\\'
		|| (*str)[i + 1] == '$' || (*str)[i + 1] == '"'))
			rm_char(str, i);
		i++;
	}
	return (i);
}
