#include "./../includes/minishell.h"

int	search_env(int i, char **str, t_mini *mini)
{
}

void	value_env(t_var *shell, char **str)
{
	int i;

	i = 0;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] && (*str)[i] == '\\')
		{
			if ((*str)[i + 1] == '$')
				rm_char(str, i);
			if ((*str)[i + 1])
				i++;
		}
		else if ((*str)[i] == '$' && (*str)[i + 1]
        && (*str)[i] != ' ')
			i += search_var(i, braces, str, param) - 1;
		i++;
	}
	return (0);
}