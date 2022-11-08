/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:26:05 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/08 18:01:00 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"
#include "../../../includes/minishell.h"

int	ft_append(t_ms **lex, char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 2;
	while (str[i] == ' ')
		i++;
	j = i;
	while ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '<')
		&& (str[i] != '>'))
		i++;
	temp = ft_substr(str, j, i - j);
	if (str[1] == '<')
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 5));
	else if (str[1] == '>')
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 6));	
	return (i);
}

int	ft_chevron(t_ms **lex, char *str, char c)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	j = 1;
	if (str[i] == c)
	{
		if (str[i + 1] == '<' || str[i + 1] == '>')
			return (-1);
		i = ft_append(lex, str);
		return (i);
	}
	while (str[j] == ' ')
		j++;
	i++;
	while ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '<')
		&& (str[i] != '>'))
		i++;
	if (i == 1)
		return (-1);
	temp = ft_substr(str, j, i - j);
	if (c == '<') 
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 3));
	else if (c == '>')
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 4));
	return (i);
}