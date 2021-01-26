/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 21:05:59 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/26 15:19:48 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void		rm_char(char **str, int j)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strduplen(*str, j);
	temp2 = ft_strdup(*str + j + 1);
	free(*str);
	*str = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
}

void		rm_token(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\n' && i == 0)
			(*str)[i] = '\0';
		if ((*str)[i] == '\a' || (*str)[i] == '\n')
			(*str)[i] = ' ';
		if ((*str)[i] == '\'')
			i = simplequote_char(str, i);
		else if ((*str)[i] == '"')
			i = doublequote_char(str, i);
		else
			i++;
		if ((*str)[i - 1] == '\r')
			(*str)[i - 1] = '\'';
		if ((*str)[i - 1] == '\b')
			(*str)[i - 1] = '"';
	}
}

static void	recurrence(t_list *lst)
{
	if (lst)
	{
		recurrence(lst->next);
		free(lst);
	}
}

void		rm_lst(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp)
		recurrence(tmp);
	*lst = NULL;
}
