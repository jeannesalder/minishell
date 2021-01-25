/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:10:22 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/25 13:10:59 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	free_multiple(void *s1, void *s2, void *s3, void *s4)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

void	free_toks(char **toks, int nbtoks)
{
	int	i;

	i = 0;
	if (!toks)
		return ;
	while (i < nbtoks)
	{
		if (toks[i])
			free(toks[i]);
		i++;
	}
	free(toks);
}