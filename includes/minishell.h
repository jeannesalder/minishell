/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 23:36:39 by jsaguez           #+#    #+#             */
/*   Updated: 2021/01/24 20:46:45 by jsaguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "structure.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>

t_var	*g_shell;
char	*g_read;

/*
 **fonctions main.c
 */

void			display(char **env);
char			*get_path(char **envp);
char			*get_cmd_path(char *path, char *cmd);

/*
 **fonctions signal.c
 */
void			sigint_handler(int signo);
void			sigquit_handler(int signo);

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
 **fonctions syntax_error.c
 */
int				syntax_error(t_var *shell, char *input);

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

/*
 **fonctions exec.c
 */
void			ft_exec(t_var *shell);
int				is_a_built(t_var *shell, char *cmd);
int				ft_exec_cmd(t_var *shell, char **cmd);

/*
 **fonctions export_utils.c
 */

void			modify_env(char **env, char *cmd, int index, t_env var);
char			**add_env(char **env, char *cmd, t_env var);
int				is_in_order(const char *s1, const char *s2);

/*
 **fonctions parsing.c
 */
void			parsing(t_mini *mini, t_var *shell, int i, int nbr);
int				s_error(t_mini *mini, t_var *shell);
int				q_error(t_mini *mini, char c1, char c2, t_var *shell);
int				space_error(t_mini *mini);

/*
 **fonctions utils.c
 */
void			free_table(char **table);
char			*ft_cat(char *g_read, char c);
char			*ft_strduplen(char *str, int len);
void			ft_addchr(char **str, char c);
char			quote_and_semi(char quote, char c);
int				quote_verif(t_mini *mini, char c, int i);

/*
 **fonctions tokens.c
 */
int				nb_tokens(char *str);
void			set_tokens(char **toks, char *str, int nbtok);
int				len_token(char *str, int i);
int				len_quote(char *str, char c);

/*
 **fonctions rm.c
 */
void			rm_char(char **str, int j);
void			rm_token(char **str);
void			rm_lst(t_list **lst);

/*
 **fonctions split_semi.c
 */
char			**split_semi(char const *s, char c, int nbr);

/*
 **fonctions value_env.c
 */
int				value_env(t_var *shell, char **str);
int				search_env(char **str, t_var *shell, int i, int brace);
int				len_env(char *str);
char			*get_envs(char **envp, char *env);

/*
 **fonctions value_env_utils.c
 */
int				value_env_simpleq(char **str, int i);
int				value_env_doubleq(char **str, t_var *shell, int i, int brace);
char			*safe_char(char **str, int i);
int				quote_char(char **str, int i);
int				doublequote_char(char **str, int i);

/*
 **fonctions pipes.c
 */
int				ft_pipes(t_var *shell, int nb_p);

/*
 **fonctions pipes_utils.c
 */
void			close_all_fd(int *pfd, int nb_p);
t_list			*split_pipes(char **cmd);
int				check_pipes(char **cmd);

/*
 **fonctions redirection.c
 */
char			**redirection(t_var *shell, char **cmd, int p);
void			redi_out(t_var *shell, char **cmd, int i, int fd);
void			redi_in(t_var *shell, char **cmd, int i, int fd);
char			**delete_redi(t_var *shell, char **cmd, int p);
int				count_redi(t_var *shell, char **cmd);

/*
 **fonctions verif_redi.c
 */
int				*verif_out(t_var *shell, int *verif);
int				nb_redi(t_var *shell);
int				*change_out(int *verif);
int				drop_redi(char **cmd, int i);
int				open_redi(t_var *shell, char **cmd, int i, int fd);

#endif
