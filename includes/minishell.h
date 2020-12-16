#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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

/*
 **fonctions env_utils.c
*/

char	*get_varenv(char **env, char *name);

/*
 **fonctions list_utils.c
*/

void	lstadd_value(t_list **list, void *value);


int	ft_exec_cmd(t_var *shell);

#endif
