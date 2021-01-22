/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaguez <jsaguez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:26:15 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/01/22 12:29:36 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_error(char *input, char c)
{
	free(input);
	ft_putstr_fd("bash: syntax error near unexpected token \'", 2);
	if (c == ' ')
		ft_putstr_fd("newline", 2);
	else
		ft_putchar_fd(c, 2);
	ft_putendl_fd("\'", 2);
	return (1);
}

int	check_chevron(char *input, char c, int j)
{
	if (c != '>')
		return (0);
	if (input[j])
	{
		if (input[j] == '<')
			return (1);
		if (input[j] == '>' && input[j + 1] != '>')
			return (1);
		if (input[j] == '>')
		{
			j = j - 1;
			while (input[j] && (input[j] == ' ' || input[j] == '\t'))
				j--;
			if (input[j] == '>')
				return (1);
		}
	}
	return (0);
}

int	check_prev(char *input, int i, char c)
{
	int	j;

	j = i - 1;
	while (input[j] && (input[j] == ' ' || input[j] == '\t'))
		j--;
	if (c == ';')
	{
		if (!input[j] || ft_charset(input[j], "<>|;"))
			return (print_error(input, c));
	}
	if (c == '|')
	{
		if (!input[j] || ft_charset(input[j], "<>|;") || !input[i + 1])
			return (print_error(input, c));
	}
	if ((c == '<' || c == '>') && !input[i + 1])
		return (print_error(input, ' '));
	if (c == '<')
		if (input[j] && (input[j] == '<' || input[j] == '>'))
			return (print_error(input, c));
	if (check_chevron(input, c, j))
		return (print_error(input, c));
	return (0);
}

int	check_quotes(int quotes, char c)
{
	if (c == '\'')
	{
		if (quotes == 0)
			quotes = 1;
		else if (quotes == 1)
			quotes = 0;
	}
	if (c == '"')
	{
		if (quotes == 0)
			quotes = 2;
		else if (quotes == 2)
			quotes = 0;
	}
	return (quotes);
}

int	syntax_error(char *input)
{
	int		i;
	int		quotes;
	int		error;
	char	c;

	i = 0;
	quotes = 0;
	error = 0;
	while (input[i])
	{
		c = input[i];
		if (c == '\"' || c == '\'')
			quotes = check_quotes(quotes, c);
		if (quotes == 0 && (c == ';' || c == '|' || c == '<' || c == '>'))
			if (check_prev(input, i, c))
				return (1);
		i++;
	}
	return (0);
}
