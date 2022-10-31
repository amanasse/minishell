/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:54:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/31 17:01:54 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*prio ' ' et " " : verifier si fermes, sinon erreur
chaque maillon = 1 mot (split espace)
types :
0 = entre guillemets OK
1 = cmd - str OK
2 = pipe　OK
3 = redirection entree < OK
4 = redirection sortie > OK
5 = redirection << (append) doit recevoir un delimiteur OK
6 = redirection sortie append (reecrit dessus) >> OK
7 = var environnement $var ???
*/

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
	return (1);
}


int	ft_check_quotes(char *str, char c)
{
	int	i;
	
	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_chevron(t_ms **lex, char *str, char c)
{
	int		i;
	int 	j;
	char	*temp;

	i = 1;
	j = 1;
	if (str[i] == c)
	{
		if (str[i + 1] == '<' || str[i + 1] == '>')
			return (-1);
		ft_append(lex, str);
		return (0);
	}
	while (str[++i] == ' ')
		i++;
	while ((str[++i] != ' ') && (str[++i] != '\0') && (str[++i] != '<')
		&& (str[++i] != '>'))
		i++;
	if (j == 1)
		return (-1);
	temp = ft_substr(str, 0, i);
	if (c == '<') 
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 3));
	else if (c == '>')
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 4));
	return (i);
	
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
			temp = ft_strncpy(str + i, j + 1);
			ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp, 0));
			i += j + 1;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			res = ft_chevron(&lex, str + i, str[i]);
			printf("res = %d\n", res);
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
			while ((str[j] != ' ') && (str[j] != '\0') && (str[j] != '<') 
				&& (str[j] != '>') && (str[j] != '|'))
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
	