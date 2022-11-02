/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:52:08 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/02 17:25:45 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
0 = entre guillemets "" OK
1 = cmd - str OK
2 = pipe　OK
3 = redirection entree < OK
4 = redirection sortie > OK
5 = redirection << (append) doit recevoir un delimiteur OK
6 = redirection sortie append (reecrit dessus) >> OK
7 = var environnement $var
fonction a faire = check si caractere est valide apres $ // ex : @ - = # & *
8 = entre ''
 */

char	*ft_clean_quotes(t_ms *temp)
{
	int		i;
	int		j;
	char 	*value;
	char	*to_replace;
	char	*tmp_str;

	i = 1;
	while (temp->str[i] != '$' && temp->str[i] != '\0' && temp->str[i] != '"')
		i++;
	if (temp->str[i] == '$')
	{
		j = i;
		tmp_str = ft_substr(temp->str, 1, j - 1);
		while (temp->str[j] != ' ' && temp->str[j] != '"')
			j++;
		to_replace = ft_substr(temp->str + i, 1, j - i - 1);
		value = getenv(to_replace);
		if (value == NULL)
			value = "";
		tmp_str = ft_strcat(tmp_str, value);
		tmp_str = ft_strcat(tmp_str, temp->str + j);
	}
	else
		return (temp->str);
	return (tmp_str);
}

void	ft_clean_lst(t_ms **lex)
{
	t_ms	*temp;

	temp = *lex;
	while (temp != NULL)
	{
		if (temp->type == 0)
			temp->str = ft_clean_quotes(temp);
		// else if (temp->type == 8)
		// 	ft_clean_simple_quotes(temp);
		temp = temp->next;
	}
}