/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 11:37:40 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/12/19 11:37:43 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int		nb_arg(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;

	return (i - 1);
}

void	lstadd_value(t_list **list, void *value)
{
	t_list *new;
	t_list *last;

	new = malloc(sizeof(new)); //utiliser bzero ? Proteger malloc.
	new->content = value;
	new->next = NULL;
	if (!(*list))
		*list = new;
	else
	{
		last = ft_lstlast(*list);
		last->next = new;
	}
}
