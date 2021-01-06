#include "./../includes/minishell.h"

static char	*ft_strdup_spe(char *s, int end, int size)
{
	char	*chaine;
	int		i;
	int		start;

	i = 0;
	start = end - size;
	chaine = malloc(sizeof(*chaine) * size + 1);
	if (chaine == 0)
		return (0);
	while (i < size)
	{
		chaine[i] = s[start + i];
		i++;
	}
	chaine[i] = '\0';
	return (chaine);
}

static char	**ft_remplissage(char *s, char c, char **point_tab)
{
	int		i;
	int		j;
	int		x;
	char	q;

	i = 0;
	j = 0;
	x = -1;
	q = ' ';
	while (s[i])
	{
		while (s[i] && s[i] == c && q == ' ')
			i++;
		while (s[i] && (s[i] != c || (s[i] == c && q != ' ')))
		{
			q = quote_and_semi(q, s[i]);
			i++;
			j++;
		}
		if (j > 0)
			point_tab[++x] = ft_strdup_spe(s, i, j);
		j = 0;
	}
	point_tab[x + 1] = 0;
	return (point_tab);
}

char	**split_semi(char const *s, char c)
{
	char	**point_tab;
	int		nbr;
	int		i;
	char	q;

	i = 1;
	nbr = 0;
	q = ' ';
	if (!s)
		return (0);
	if (s[0] == '\0')
	{
		point_tab = malloc(sizeof(*point_tab) * 1);
		return (ft_remplissage((char *)s, c, point_tab));
	}
	while (s[i])
	{
		q = quote_and_semi(q, s[i]);
		if (s[i] == c && s[i - 1] != c && q == ' ')
			nbr++;
		i++;
	}
	if (s[i - 1] != c)
		nbr++;
	point_tab = malloc(sizeof(*point_tab) * (nbr + 1));
	if (point_tab == 0)
		return (0);
	return (ft_remplissage((char *)s, c, point_tab));
}
