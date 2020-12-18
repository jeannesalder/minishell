#include "./../includes/minishell.h"

int	is_in_order(const char *s1, const char *s2)
{
	if (ft_memcmp(s1, s2, ft_strlen(s1) + 1) <= 0)
		return (1);
	return (0);
}

char **sort_env(char **cpy)
{
	int i;
	int j;
	char *tmp;
//	char **cpy;

//	cpy = cpy_env(env);
	i = 0;
	while (cpy[i + 1])
	{
		j = i + 1;
		while (cpy[j])
		{
			if (!(is_in_order(cpy[i], cpy[j])))
			{
				tmp = cpy[i];
				cpy[i] = cpy[j];
				cpy[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (cpy);
}

void	print_env(char **env)
{
	int		i;
	t_env	tmp;

	i = 0;
	while (env[i])
	{
		tmp = split_env(env[i]);
		if (ft_strncmp(tmp.name, "_", 2) != 0)
		{
			// ft_print("declare -x %s", tmp.name);
			ft_putstr_fd("declare -x ", 1); //a remplacer par le printf
			ft_putstr_fd(tmp.name, 1);
			if (tmp.content == 1)
				// ft_print("=\"%s\"", tmp.value);
			{
				ft_putstr_fd("=\"", 1); //a remplacer par le printf
				ft_putstr_fd(tmp.value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putchar_fd('\n', 1);
		}
		free(tmp.name);
		free(tmp.value);
		i++;
	}
	free_strarray(env);
}

int	ft_export(char **env, char **cmd)
{
	if (!(cmd[1]))
		print_env(sort_env(cpy_env(env)));
	return (1);
}