#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>

typedef struct		s_var
{
	char	*pwd;
	char	*path;
	char	**cmd;
	char	**env;
}					t_var;

typedef struct	s_env
{
	char *name;
	int	content;
	char	*value;
}	t_env;

/*
 **fonctions main.c
*/

char	*ft_cat(char *input, char c);
char	*ft_read_input();
char	*get_path(char **envp);
char *get_cmd_path(char *path, char *cmd);
void sigint_handler(int signo);

/*
 **fonctions builtin.c
*/

int	ft_cd(t_var *shell, char **cmd);
int ft_pwd(t_var *shell);
int ft_echo(t_var *shell, char **cmd);

/*
 **fonctions env_utils.c
*/

char	*get_varenv(char **env, char *name);
char	**cpy_env(char **env);
t_env	split_env(char *var);
/*
 **fonctions ft_export.c
*/

char	**sort_env(char **env);
int	ft_export(char **env, char **cmd);

/*
 **fonctions list_utils.c
*/

void	lstadd_value(t_list **list, void *value);

/*
 **fonctions list_utils.c
*/

void	free_strarray(char **tab);



int	ft_exec_cmd(t_var *shell);


#endif
