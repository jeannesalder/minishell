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
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_env
{
	char	*name;
	int		content;
	int		append;
	char	*value;
}				t_env;

typedef struct          s_mini
{
        char    *str;
        char    **cmds;
        int             nbtok;
        char    **toks;
}                                       t_mini;

typedef struct s_var
{
	char	*pwd;
	char	*path;
	char	**cmd;
	char	**env;
	int	ret;
	int	fork;	
	t_mini	*mini;	
}				t_var;


t_var	*g_shell;
char 	*g_read;

/*
 **fonctions main.c
*/

void			display(char **env);
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
void			free_and_exit(t_var *shell, int nb_exit, int eof);
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

void			modify_env(char **env, char *cmd, int index, t_env var);
char			**add_env(char **env, char *cmd, t_env var);
int				is_in_order(const char *s1, const char *s2);

/*
 **fonctions parsing.c
*/
void                            parsing(t_mini *mini, t_var *shell);
int                                     s_error(t_mini *mini);
int                                     q_error(t_mini *mini, char c1, char c2);

/*
 **fonctions utils.c
*/
void                            free_table(char **table);
char							*ft_cat(char *g_read, char c);
char                            *ft_strduplen(char *str, int len);
void                            ft_addchr(char **str, char c);
char                            quote_and_semi(char quote, char c);

/*
 **fonctions tokens.c
*/
int                                     nb_tokens(char *str);
void                            set_tokens(char **toks, char *str, int nbtok);
int                                     len_token(char *str, int i);
int                                     len_quote(char *str, char c);

/*
 **fonctions rm.c
*/
void                            rm_char(char **str, int j);
void                            rm_token(char **str);

/*
 **fonctions split_semi.c
*/
char            **split_semi(char const *s, char c);

#endif
