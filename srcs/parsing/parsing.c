/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 20:08:29 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/26 15:33:44 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		space_error(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->str[i] && (mini->str[i] == ' ' || mini->str[i] == '\t'))
		i++;
	if (!(mini->str[i]))
	{
		free(mini->str);
		return (1);
	}
	return (0);
}

int		q_error(t_mini *mini, char c1, char c2, t_var *shell)
{
	int	i;

	i = 0;
	while (mini->str[i])
	{
		if (mini->str[i] == c1 && nb_backslash(mini->str, i) == 0)
		{
			i++;
			while (mini->str[i] && mini->str[i] != c1)
				i++;
		}
		i = quote_verif(mini, c2, i);
		if (!mini->str[i])
		{
			ft_putstr_fd("Non finished quotes\n", 2);
			shell->ret = 2;
			free(mini->str);
			return (1);
		}
		i++;
	}
	return (0);
}

int		s_error(t_mini *m, t_var *shell)
{
	int		i;
	int		j;
	char	q;

	i = 0;
	j = 0;
	q = ' ';
	while (m->str && m->str[i])
	{
		q = quote_and_semi(q, m->str[i]);
		if (m->str[i] == ';' && q == ' ')
			j--;
		if (m->str[i] != ';' && m->str[i] != ' ' && j >= 0 && q == ' ')
			j = 1;
		i++;
	}
	if (!m->str || j < 0)
	{
		if (j < 0)
			ft_putstr_fd("-bash; syntax error near unexpected token `;'\n", 2);
		shell->ret = 2;
		free(m->str);
		return (1);
	}
	return (0);
}

void	parsing(t_mini *mini, t_var *shell, int i, int nbr)
{
	if (syntax_error(shell, mini->str) || s_error(mini, shell)
	|| q_error(mini, '\'', '"', shell) || space_error(mini))
		return ;
	mini->cmds = split_semi(mini->str, ';', nbr);
	while (mini->cmds[i])
	{
		value_env(shell, &(mini->cmds[i]));
		mini->nbtok = nb_tokens(mini->cmds[i], &(mini->nbtemp));
		shell->cmd = (char **)ft_calloc(sizeof(char *), (mini->nbtok + 1));
		set_tokens(shell->cmd, mini->cmds[i], mini->nbtok);
		if (shell->cmd[0] && ft_exec_cmd(shell, shell->cmd))
		{
			free_table(shell->cmd);
			break ;
		}
		i++;
		free_table(shell->cmd);
	}
	if (g_read[0] != '\0')
		free(mini->str);
	else
		free(g_read);
	free_table(mini->cmds);
	return ;
}
