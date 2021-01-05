#include "./../includes/minishell.h"

int	q_error(t_mini *mini, char c1, char c2)
{
	int	i;

	i = 0;
	while (mini->str[i])
	{
		if (mini->str[i] == c1)
		{
			i++;
			while (mini->str[i] && (mini->str[i] != c1))
				i++;
		}
		if (mini->str[i] == c2)
		{
			i++;
			while (mini->str[i] && (mini->str[i] != c2))
				i++;
		}
		if (!mini->str[i])
		{
			ft_putstr_fd("Non finished quotes\n", 2);
			free(mini->str);
			mini->str = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

int	s_error(t_mini *m)
{
    int 	i;
    int 	j;
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
		free(m->str);
		m->str = 0;
		return (1);
	}
	return (0);
}

void		parsing(t_mini *mini, t_var *shell)
{
	int i;

	if (s_error(mini) || q_error(mini, '\'', '"'))
		return ;
	mini->cmds = split_semi(mini->str, ';');
	i = 0;
	while (mini->cmds[i])
	{
		//check_env(&(mini->cmds[i]), mini);Modification par rapport a backslash et variable d'environnement
		mini->nbtok = nb_tokens(mini->cmds[i]);
		mini->toks = (char **)ft_calloc(sizeof(char *), (mini->nbtok + 1));
		set_tokens(mini->toks, mini->cmds[i], mini->nbtok);
		shell->cmd = mini->toks;
		ft_exec_cmd(shell);
//		free_strarray(shell->cmd);
		i++;
		free_table(mini->toks);
	}
	free(mini->str);
	mini->str = 0;
	free_table(mini->cmds);
    return ;
}
