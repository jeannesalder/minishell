/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2021/01/19 14:52:36 by jgonfroy	       #+#    #+#	      */
/*   Updated: 2021/01/21 18:32:49 by jgonfroy         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_env
{
	char	*name;
	int		content;
	int		append;
	char	*value;
}		t_env;

typedef struct s_mini
{
	char	*str;
	char	**cmds;
	int		nbtok;
	int		nbtemp;
	char	**toks;
}		t_mini;

typedef struct s_var
{
	char	*pwd;
	char	*path;
	char	**cmd;
	char	**env;
	int		ret;
	int		fork;
	int		in;
	int		out;
	t_mini	*mini;	
	t_list	*pipe;
}		t_var;

#endif
