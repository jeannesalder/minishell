/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 21:23:09 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/24 18:30:14 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_cat(char *input, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (input[i])
		i++;
	str = malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (input[i])
	{
		str[i] = input[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = 0;
	free(input);
	return (str);
}

char	*ft_strduplen(char *str, int len)
{
	char	*dest;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (str[size])
		size++;
	if (len < size)
		size = len;
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	quote_and_semi(char quote, char c)
{
	char	q;

	q = quote;
	if ((q == '\'' && c == '\'') || (q == '"' && c == '"'))
		q = ' ';
	else if (q == ' ' && (c == '\'' || c == '"'))
		q = c;
	return (q);
}

int		quote_verif(t_mini *mini, char c, int i)
{
	if (mini->str[i] == c && mini->str[i - 1] != '\\')
	{
		i++;
		while (mini->str[i] && (mini->str[i] != c
		|| (mini->str[i] == c && mini->str[i - 1] == '\\')))
			i++;
	}
	return (i);
}
