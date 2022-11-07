/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:54:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/07 16:32:37 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

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

int	ft_lexer(t_ms *lex, char *str)
{
	int		i;
	int		j;
	int		res;
	char	*temp;
	int	 	closed;

	i = 0;
	closed = char_is_quote(str, '"');
	if (closed % 2 != 0)
		return (-1);
	closed = char_is_quote(str, '\'');
	if (closed % 2 != 0)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{			
			j = i + 1;
			while (str[j] != '"')
				j++;
			while (char_is_space(str[j]) == 0 && str[j] != '\0')
				j++;
			temp = ft_strncpy(str + i, j - i);
			ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp, 0));
			i = j;
		}
		else if (str[i] == '\'')
		{			
			j = i + 1;
			while (str[j] != '\'')
				j++;
			while (char_is_space(str[j]) == 0 && str[j] != '\0')
				j++;
			temp = ft_strncpy(str + i, j - i);
			ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp, 8));
			i = j;
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
			while ((char_is_separator(str[j]) == 0) && (char_is_space(str[j]) == 0)
				&& (str[j] != '\0'))
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

