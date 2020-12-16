#include "./../includes/minishell.h"

char	*get_varenv(char **env, char *name)
{
	int i;
	int size;

	size = ft_strlen(name);
	i = 0;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], name, size) == 0)
			return (ft_substr(env[i], size, ft_strlen(env[i]) - size));
		i++;
	}
	return (NULL);
}