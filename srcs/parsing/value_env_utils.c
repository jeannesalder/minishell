/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:41:56 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/26 15:19:07 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		value_env_doubleq(char **str, t_var *shell, int i, int brace)
{
	i++;
	while ((*str)[i] && ((*str)[i] != '"'))
	{
		if ((*str)[i] == '$' && (*str)[i + 1]
		&& ((*str)[i + 1] == '?' || ft_isalnum((*str)[i + 1])
		|| ((*str)[i + 1] == '{')))
			i += search_env(str, shell, i, brace) - 1;
		if ((*str)[i] == '\\' && ((*str)[i + 1] == '\\'
		|| (*str)[i + 1] == '$' || (*str)[i + 1] == '"'))
		{
			rm_char(str, i);
			if ((*str)[i] == '"')
				(*str)[i] = '\b';
		}
		i++;
	}
	return (i);
}

char	*safe_char(char **str, int i)
{
	if ((*str)[i] == '\\' && (*str)[i + 1] && (*str)[i + 1] == ' '
		&& (((*str)[i - 1] && (*str)[i - 1] == ' ') && ((*str)[i + 2]
		&& (*str)[i + 2] == ' ')))
		(*str)[i] = '\a';
	else if ((*str)[i] == '\\' && (*str)[i + 1] && (*str)[i + 1] == ' '
		&& (((*str)[i - 1] && (*str)[i - 1] == ' ') || ((*str)[i + 2]
		&& (*str)[i + 2] == ' ')))
		(*str)[i] = '\n';
	if ((*str)[i] == '\\' && (*str)[i + 1] && (*str)[i + 1] == '"')
		(*str)[i + 1] = '\b';
	if ((*str)[i] == '\\' && (*str)[i + 1] && (*str)[i + 1] == '\'')
		(*str)[i + 1] = '\r';
	return ((*str));
}

int		simplequote_char(char **str, int i)
{
	rm_char(str, i);
	i++;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	rm_char(str, i);
	return (i);
}

int		doublequote_char(char **str, int i)
{
	rm_char(str, i);
	while ((*str)[i] && (*str)[i] != '"')
	{
		if ((*str)[i] == '\b')
			(*str)[i] = '"';
		i++;
	}
	if ((*str)[i] != '"')
		rm_char(str, i);
	return (i);
}
