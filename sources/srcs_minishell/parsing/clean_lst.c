/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:52:08 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/09 12:21:28 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"
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
fonction a faire = check si caractere est valide apres $ // ex : @ - = # *
8 = entre ''
 */

char	*ft_replace_var(char *str)
{
	int		i;
	int		j;
	char 	*value;
	char	*to_replace;
	char	*tmp_str;

	i = 0;
	tmp_str = NULL;
	while (str[i] != '$' && str[i] != '\0')
		i++;
	if (str[i] == '$')
	{
		if (i > 0)
		{
			tmp_str = ft_substr(str, 0, i);
			if (tmp_str == NULL)
				return (NULL);
		}
		j = i;
		while (str[j] != ' ' && str[j] != '\0' && str[j] != '"')
			j++;
		to_replace = ft_substr(str + i, 1, j - 1);
		if (to_replace == NULL)
			return (NULL);
		value = getenv(to_replace);
		if (value == NULL)
			value = "";
		if (!tmp_str)
			tmp_str = ft_strdup(value);
		else
			tmp_str = ft_strcat(tmp_str, value);
	}
	else
		return (str);
	return (tmp_str);
}


void	ft_clean_lst(t_ms **lex)
{
	t_ms	*temp;
	int		count;

	temp = *lex;
	count = 0;
	while (temp != NULL)
	{
		if (temp->type == 0 || temp->type == 1 || temp->type == 3
			|| temp->type == 4 || temp->type == 5 || temp->type == 6)
			temp->str = ft_clean_if_quotes(temp->str);
		else if ( temp->type == 8)
			temp->str = ft_clean_simple_quotes(temp->str);
		else if (temp->type == 2)
			count++;
		temp = temp->next;
	}
	ft_view_lst(*lex);
	ft_build_struc_parse(lex, count);
}
