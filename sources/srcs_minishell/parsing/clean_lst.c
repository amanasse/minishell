/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:52:08 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/02 12:45:59 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
0 = entre guillemets OK
1 = cmd - str OK
2 = pipe　OK
3 = redirection entree < OK
4 = redirection sortie > OK
5 = redirection << (append) doit recevoir un delimiteur OK
6 = redirection sortie append (reecrit dessus) >> OK
7 = var environnement $var ??? fonction a faire = check si caractere est valide apres $ ex : $1 = OK, $a = OK, $@ = KO, $- = KO
*/

void	ft_clean_quotes(t_ms *temp)
{
	int		i;
	int		j;
	char	*str;
	t_ms	*temp_lst;

	str = temp->str;
	i = 1;
	while (str[i] != '$' && str[i] != '\0')
		i++;
	if (str[i] == '$')
	{
		j = i - 1;
		while (str[j] != ' ' && str[j] != '\0' && str[i] != '\'' && str[j] != '"')
			j++;
		temp->str = ft_substr(str, 1, i - 1);
		temp_lst = temp->next;
		printf("str[j] = %c\n", str[j]);
		printf("j = %d\n", j);
		temp->next = ft_lstnew_ms(ft_substr(str + i, 0, j - i), 7);
		printf("temp->next->str = %s\n", temp->next->str);
		temp->next->next = temp_lst;
	}
}

void	ft_clean_lst(t_ms **lex)
{
	t_ms	*temp;

	temp = *lex;
	while (temp != NULL)
	{
		if (temp->type == 0)
			ft_clean_quotes(temp);		
		temp = temp->next;
	}
}