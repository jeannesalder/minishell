#include "./../includes/minishell.h"

char	*get_envs(char **export, char *env)
{
	int		i;
	int		len;
	char	*tmp;

	env = ft_strjoin(env, "=");
	len = strlen(env);
	i = 0;
	while (export[i] && ft_memcmp(env, export[i], len))
		i++;
	if (export[i])
		tmp = export[i] + len;
	else
		tmp = "\0";
	free(env);
	return (tmp);
}

int	    len_env(char *str)
{
	int		i;

	i = 0;
    if (str[i] && str[0] == '{')
        i++;
	while (str[i] && !(ft_isdigit(str[0]))
		&& (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

int    begin_env(char **str, int i, int brace)
{
    if ((*str)[i + 1] == '{')
		brace = 1;
    return (brace);
}

int	    search_env(char **str, t_var *shell, int i, int brace)
{
	char	*temp1;
	char	*temp2;
	char	*env;
	int		len;

	env = 0;
    brace = begin_env(str, i, brace);
	if ((*str)[i + 1 + brace] == '?')
		env = ft_itoa(shell->ret);
    len = len_env(*str + i + 1);
	if (!(env))
	{
		env = ft_strduplen(*str + i + 1 + brace, len - brace);
        env = ft_strdup(get_envs(shell->env, env));
        if (brace == 1 && (*str)[i + 1 + len] != '}')
        {
            free(env);
            env = ft_strdup("\0");
            brace = 0;
        }
	}
	temp1 = ft_strduplen(*str, i);
	temp2 = ft_strdup(*str + i + len + 1 + brace);
	free(*str);
	*str = ft_strjoin(ft_strjoin(temp1, env), temp2);
    free_multiple(temp1, temp2, env, NULL);
	return (ft_strlen(env));
}

int     value_env(t_var *shell, char **str)
{
	int	i;
    int brace;

	i = 0;
    brace = 0;
	while ((*str) && (*str)[i])
	{
        if ((*str)[i] == '$' && (*str)[i + 1]
			&& (*str)[i] != ' ')
			i += search_env(str, shell, i, brace) - 1;
		i++;
	}
	return (0);
}