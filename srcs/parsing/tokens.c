/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 21:00:25 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/24 14:51:57 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		len_quote(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int		len_token(char *str, int i)
{
	int	j;

	j = 0;
	if (str[i] == '>' && str[i + 1] == '>')
		j = 2;
	else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		j = 1;
	else
	{
		while (str[i + j] && str[i + j] != ' ' && str[i + j] != '>'
			&& str[i + j] != '<' && str[i + j] != '|' && str[i + j] != '\t')
		{
			if (str[i + j] == '\'' || str[i + j] == '"')
			{
				j++;
				j += len_quote(str + i + j, str[i - 1 + j]);
			}
			j++;
		}
	}
	return (j);
}

void	set_tokens(char **toks, char *str, int nbtok)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (j < nbtok && str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		len = len_token(str, i);
		toks[j] = ft_strduplen(str + i, len);
		rm_token(&(toks[j]));
		j++;
		i += len;
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
	}
}

int		nb_tokens(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		j++;
		i += len_token(str, i);
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
	}
	return (j);
}
