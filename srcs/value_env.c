#include "./../includes/minishell.h"

int	search_env(int i, char **str, t_var *shell)
{
	char	*temp1;
	char	*temp2;
	char	*env;
	int		len;
	int		brace;

	brace = 0;
	env = 0;
	if ((*str)[i + 1] == '{')
		brace = 1;
	if ((*str)[i + 1 + brace] == '?')
		env = ft_itoa(shell->ret);
	len = len_env(*str + i + 1 + brace, brace);
	temp1 = ft_strduplen(*str, i);
}

int		len_env(char *str, int brace)
{
	int		i;

	i = 0;
	while (str[i] && !(ft_isdigit(str[0])) 
	&& ft_isalnum(str[i]) || str == '_'))
	{
		i++;
	}
	return (i);
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