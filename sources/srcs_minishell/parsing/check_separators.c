/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:26:05 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/25 17:53:14 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_is_separator(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\0')
		return (1);
	return (0);
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
