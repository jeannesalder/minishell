#include "./../includes/minishell.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
		free(table[i++]);
	free(table);
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
	if (!(dest = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void		ft_addchr(char **str, char c)
{
	char	*temp;

	temp = ft_calloc(sizeof(char), ft_strlen(*str) + 2);
	ft_memcpy(temp, *str, ft_strlen(*str));
	temp[ft_strlen(temp)] = c;
	if (*str)
		free(*str);
	*str = temp;
}

char		quote_and_semi(char quote, char c)
{
	char q;

	q = quote;
	if ((q == '\'' && c == '\'')
    || (q == '"' && c == '"'))
        q = ' ';
    else if (q == ' ' && (c == '\'' || c == '"'))
    	q = c;
//	else
//		q = q;
	return (q);
}
