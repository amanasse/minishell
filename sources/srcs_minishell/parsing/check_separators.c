/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:26:05 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/17 17:02:12 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append(t_lstms *lex, char *str)
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
	if (temp == NULL)
		return (0);
	if (str[1] == '<')
		ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp, 5));
	else if (str[1] == '>')
		ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp, 6));
	return (i);
}

int	ft_chevron(t_lstms *lex, char *str, char c)
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
		return (ft_append(lex, str));
	}
	while (str[j] == ' ')
		j++;
	i++;
	while ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '<')
		&& (str[i] != '>'))
		i++;
	temp = ft_substr(str, j, i - j);
	if (temp == NULL)
		return (-1);
	if (c == '<') 
		ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp, 3));
	else if (c == '>')
		ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp, 4));
	return (i);
}

int	char_is_separator(char c)
{
	if (c ==  '<' || c ==  '>' || c == '|' || c == '\0')
		return (1);
	return (0);
}

int	char_is_space(char c)
{
	if (c ==  ' ')
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
