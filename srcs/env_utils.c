#include "./../includes/minishell.h"

char	*get_varenv(char **env, char *name)
{
	int i;
	int size;

	size = ft_strlen(name);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, size) == 0)
			return (ft_substr(env[i], size, ft_strlen(env[i]) - size));
		i++;
	}
	return (NULL);
}

char **cpy_env(char **env)
{
	int i;
	char **tab;

	i = 0;
	while (env[i])
		i++;
	if (!(tab = ft_calloc(sizeof(char*), i + 1)))
		return (NULL);
	i = 0;
	while(env[i])
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	return (tab);
}

t_env	split_env(char *var)
{
	int index;
	t_env dest;

	if (!(index = ft_charset('=', var)))
		dest.content = 0;
	else
	{
		dest.content = 1;
		dest.name = ft_substr(var, 0, index - 1);
		dest.value = ft_substr(var, index, ft_strlen(var) - index);
	}
	return (dest);
}