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

/*
 **fonctions main.c
*/

char	*ft_cat(char *input, char c);
char	*ft_read_input();
char	*get_path(char **envp);
char *get_cmd_path(char *path, char *cmd);
int	ft_exec_cmd(char **envp, char *path, char *cmd);
void sigint_handler(int signo);

/*
 **fonctions builtin.c
*/

int	ft_cd(char *path);
int ft_pwd(void);

#endif
