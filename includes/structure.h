/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:27:01 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/26 11:54:42 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct	s_env
{
	char	*name;
	int		content;
	int		append;
	char	*value;
}				t_env;

typedef struct	s_mini
{
	char	*str;
	char	**cmds;
	int		nbtok;
	int		nbtemp;
	char	**toks;
}				t_mini;

typedef struct	s_var
{
	char	*pwd;
	char	*path;
	char	**cmd;
	char	**env;
	int		ret;
	int		fork;
	int		in;
	int		out;
	int		redi;
	t_mini	*mini;
	t_list	*pipe;
}				t_var;

#endif
