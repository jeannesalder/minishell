/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:12:02 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/12/19 09:12:04 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	change_pwd(t_var *shell)
{
	free(shell->pwd);
	shell->pwd = getcwd(NULL, 0);
	//attention : initialiser la variable PWD si jamais elle n'existe pas. A verifier !
	//besoin d'avoir creer les builtin d'environnemet
}

int		ft_cd(t_var *shell, char **cmd)
{
	char *path;

	// traiter cas too many arguments ?? ou Juju verifie avant ?
	if (cmd[1] == NULL)
	{
		if (!(path = get_varenv(shell->env, "HOME=")))
		{
			ft_putendl_fd("HOME NOT SET", 1); //chercher phrase d'erreur
			return (1); //gerer erreur;
		}
		if (chdir(path) == -1) //est-ce qu'on peut mettre la meme phrase d'erreur ?
		{
			ft_putendl_fd("No such file or directory", 1); //chercher phrase d'erreur
			return (1); //gerer erreur;
		}
	}
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			ft_putendl_fd("No such file or directory", 1); //chercher phrase d'erreur
			return (1); //gerer erreur;
		}
	}
	change_pwd(shell);
	return (0);
}
