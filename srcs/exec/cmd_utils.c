/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 11:37:40 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/22 21:19:28 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cmd_path(char *path, char *cmd)
{
	int			i;
	char		*tmp;
	char		*cmd_path;
	char		**path_split;
	struct stat	file;

	i = 0;
	if (ft_charset('/', cmd))
		return (ft_strdup(cmd));
	path_split = ft_split(path, ':');
	while (path_split[i] != NULL)
	{
		tmp = ft_strjoin(path_split[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (stat(cmd_path, &file) == 0)
		{
			free_table(path_split);
			return (cmd_path);
		}
		i++;
		free(cmd_path);
	}
	free_table(path_split);
	return (NULL);
}

int		nb_arg(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i - 1);
}

void	print_str_fd(char *s1, char *s2, char *s3, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	ft_putstr_fd(s3, fd);
}
