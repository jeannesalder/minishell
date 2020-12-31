/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:59:48 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/12/21 21:59:53 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <errno.h>

typedef struct	s_var
{
	char	*pwd;
	char	*path;
	char	**cmd;
	char	**env;
	int		ret;
}				t_var;

typedef struct	s_env
{
	char	*name;
	int		content;
	char	*value;
}				t_env;

/*
 **fonctions main.c
*/

char			*ft_cat(char *input, char c);
char			*ft_read_input();
char			*get_path(char **envp);
char			*get_cmd_path(char *path, char *cmd);
void			sigint_handler(int signo);

/*
 **fonctions builtin.c
*/

void			ft_cd(t_var *shell, char **cmd);
void			ft_pwd(t_var *shell);
void			ft_echo(t_var *shell, char **cmd);

/*
 **fonctions env_utils.c
*/

char			*get_varenv(char **env, char *name);
char			**cpy_env(char **env);
t_env			split_env(char *var);

/*
 **fonctions export_unset_utils.c
*/
int				size_env(char **env);
int				is_in_env(char **env, char *name);
int				error_id(t_var *shell, char *arg);
int				is_valid_id(t_var *shell, char *name, char *arg);

/*
 **fonctions ft_export.c
*/

char			**sort_env(char **env);
void			ft_export(t_var *shell, char **env, char **cmd);

/*
 **fonctions ft_unset.c
*/

void			ft_unset(t_var *shell, char **cmd);

/*
 **fonctions ft_env.c
*/
void			ft_env(t_var *shell, char **env);

/*
 **fonctions ft_exit.c
*/
void			ft_exit(t_var *shell, char **cmd);

/*
 **fonctions cmd_utils.c
*/

int				nb_arg(char **cmd);
void			print_str_fd(char *s1, char *s2, char *s3, int fd);
void			lstadd_value(t_list **list, void *value);

/*
 **fonctions free_utils.c
*/

void			free_multiple(void *s1, void *s2, void *s3, void *s4);
void			free_strarray(char **tab);


int				ft_exec_cmd(t_var *shell);

/*
 **fonctions export_utils.c
*/

void			modify_env(char **env, char *cmd, int index);
char			**add_env(char **env, char *cmd);

#endif
