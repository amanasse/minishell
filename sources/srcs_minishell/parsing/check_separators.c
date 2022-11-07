/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:26:05 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/07 16:32:13 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

int	ft_append(t_ms **lex, char *str)
{
	char	*temp;
	int		i;

	i = 2;
	while (str[i] == ' ')
		i++;
	while ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '<')
		&& (str[i] != '>'))
		i++;
	temp = ft_substr(str, 0, i);
	if (str[1] == '<')
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 5));
	else if (str[1] == '>')
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 6));	
	return (i);
}


// int	ft_check_quotes(char *str, char c)
// {
// 	int	i;
	
// 	i = 1;
// 	while (str[i])
// 	{
// 		printf("str[i] = %c\n", str[i]);
// 		if (str[i] == c)
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

int	ft_chevron(t_ms **lex, char *str, char c)
{
	int		i;
	char	*temp;

	i = 1;
	if (str[i] == c)
	{
		if (str[i + 1] == '<' || str[i + 1] == '>')
			return (-1);
		i = ft_append(lex, str);
		return (i);
	}
	while (str[i] == ' ')
		i++;
	while ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '<')
		&& (str[i] != '>'))
		i++;
	if (i == 1)
		return (-1);
	temp = ft_substr(str, 0, i);
	if (c == '<') 
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 3));
	else if (c == '>')
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 4));
	return (i);
}