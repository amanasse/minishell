/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:26:05 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/07 15:45:04 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_is_separator(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\0')
		return (1);
	return (0);
}

int	while_char_is_caract(char *str, int i)
{
	while (str[i + 1] != ' ' && str[i + 1] != '\0'
		&& str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1] != '/')
			i++;
	return (i);
}

int	char_is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	char_is_quote(char *str, char c)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i])
	{
		if (c == str[i])
			check++;
		i++;
	}
	return (check);
}

int	check_if_quotes_are_closed(char *str, int i)
{
	int	in_s_quotes;
	int	in_d_quotes;

	in_s_quotes = 0;
	in_d_quotes = 0;
	while (str[++i] && str)
	{
		if (str[i] == '\'')
		{
			if ((in_s_quotes == 0 && in_d_quotes == 1) || (in_s_quotes == 1))
				in_s_quotes = 0;
			else
				in_s_quotes = 1;
		}
		if (str[i] == '"')
		{
			if ((in_d_quotes == 0 && in_s_quotes == 1) || (in_d_quotes == 1))
				in_d_quotes = 0;
			else
				in_d_quotes = 1;
		}
	}
	if (in_s_quotes == 0 && in_d_quotes == 0)
		return (1);
	return (0);
}
