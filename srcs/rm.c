#include "./../includes/minishell.h"

void	rm_char(char **str, int j)
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

void	rm_token(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			rm_char(str, i);
			while ((*str)[i] && (*str)[i] != '\'')
				i++;
			rm_char(str, i);
		}
		else if ((*str)[i] == '"')
		{
			rm_char(str, i);
			while ((*str)[i] && (*str)[i] != '"')
				i++;
			rm_char(str, i);
		}
		else if (((*str)[i] == '\\') && ((*str)[i + 1] == '\\'
					|| (*str)[i + 1] == '"' || (*str)[i + 1] == '\''))
			rm_char(str, i++);
		else
			i++;
	}
}
