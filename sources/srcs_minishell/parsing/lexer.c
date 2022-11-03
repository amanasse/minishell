/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:54:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/03 17:26:16 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*prio ' ' et " " : verifier si fermes, sinon erreur
chaque maillon = 1 mot
types :
0 = entre guillemets OK
1 = cmd - str OK
2 = pipe　OK
3 = redirection entree < OK
4 = redirection sortie > OK
5 = redirection << (append) doit recevoir un delimiteur OK
6 = redirection sortie append (reecrit dessus) >> OK
7 = var environnement $var ??? OK 
8 = entre '' OK
*/



int	char_is_separator(char c)
{
	if (c ==  '<' || c ==  '>' || c == '|' || c == '\0' || c == '\'' || c == '"')
		return (1);
	return (0);
}

int	char_is_space(char c)
{
	if (c ==  ' ')
		return (1);
	return (0);
}

int	ft_lexer(t_ms *lex, char *str)
{
	int		i;
	int		j;
	int		res;
	char	*temp;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{			
			j = ft_check_quotes(str + i, str[i]);
			if (j == 0)
				return (0);
			while ((char_is_separator(str[j + 1]) == 0) && (char_is_space(str[j + 1]) == 0))
				j++;
			temp = ft_strncpy(str + i, j + 1);
			if (str[i] == '"')
				ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp, 0));
			else if (str[i] == '\'')
				ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp, 8));
			i += j + 1;

			
		}

		
		else if (str[i] == '<' || str[i] == '>')
		{
			res = ft_chevron(&lex, str + i, str[i]);
			i += res + 1;
			if (res == 0)
				i++;
			else if (res == -1)
			{	
				printf("syntax error near unexpected token '%c'\n", str[i]);
				return (0);
			}
		}


		
		else if (str[i] == '|')
		{
			ft_lstadd_back_ms(&lex, ft_lstnew_ms("|", 2));
			i++;
		}

		
		else if (str[i] == ' ')
			i++;
		
		
		else
		{
			j = i;
			while ((char_is_separator(str[j]) == 0) && (char_is_space(str[j]) == 0))
				j++;
			temp = ft_substr(str + i, 0, j - i);
			ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp, 1));
			i = j;
		}
	}
	ft_view_lst(lex);
	ft_clean_lst(&lex);
	ft_view_lst(lex);
	return (1);
}




/*

trigger

if double quote == 0

if single quote == 1


while (char_is_espace(str[i]) == 0 && char_is_separateur == 0 && trigger == 0


*/