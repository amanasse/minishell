/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:52:08 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/31 17:03:43 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
0 = entre guillemets OK
1 = cmd - str OK
2 = pipe　OK
3 = redirection entree < OK
4 = redirection sortie > OK
5 = redirection << (append) doit recevoir un delimiteur OK
6 = redirection sortie append (reecrit dessus) >> OK
7 = var environnement $var ???
*/

void	ft_clean_quotes(t_ms *temp)
{
	int		i;
	// int		j;
	char	*str;

	str = temp->str;
	i = 1;
	// j = 0;
	while (str[i])
	{
		while (str[i] != '$')
			i++;
		temp->str = ft_substr(str, 0, i - 1);
		temp->type = 1;
		// if (str[i] == '$')
		// {
		// 	while (str[j] != ' ' && str[j] != '\0' && str[j] != str[0])
		// 		j++;
		// 	temp->str = ft_substr(str + i, 0, j);
		// }
	}
}

void	ft_clean_lst(t_ms **lex)
{
	t_ms	*temp;

	temp = *lex;
	while (temp)
	{
		if (temp->type == 0)
			ft_clean_quotes(temp);
		printf("temp->str = %s\n", temp->str);
		temp = temp->next;
	}
}