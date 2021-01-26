/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:03:44 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/26 16:15:06 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int             set_fd_pipe(int *pfd, int nb)
{
        int     i;

        i = 0;
        while (i < nb)
        {
                if (pipe(pfd + 2 * i) == -1)
                        return (EXIT_FAILURE);
                i++;
        }
        return (0);
}

void    dup_fd(t_var *shell, int *pfd, int pos, int nb_p)
{
        if (pos != 1 && shell->in == 0)
                dup2(pfd[(2 * pos - 4)], 0);
        if (pos != nb_p + 1 && shell->out == 0)
                dup2(pfd[2 * pos - 1], 1);
        close_all_fd(pfd, nb_p);
}

void    close_all_fd(int *pfd, int nb_p)
{
        int     i;

        i = 0;
        while (i < nb_p * 2)
        {
                if (close(pfd[i]))
                        exit(EXIT_FAILURE);
                i++;
        }
}

