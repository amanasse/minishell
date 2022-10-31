/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:54:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/31 13:00:17 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*prio ' ' et " " : verifier si fermes, sinon erreur
chaque maillon = 1 mot (split espace)
types :
1 = cmd
2 = pipe
3 = redirection entree <
4 = redirection sortie >
5 = redirection << (append) doit recevoir un delimiteur
6 = redirection sortie append (reecrit dessus) >>
7 = var environnement $var
*/

int	ft_append(t_ms **lex, char *str)
{
	char	*temp;
	int		i;

	i = 2;
	while (str[i] == ' ')
		i++;
	while ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '<') && (str[i] != '>'))
		i++;
	temp = ft_substr(str, 0, i);
	printf ("temp = %s\n", temp);
	ft_lstadd_back_ms(lex, ft_lstnew_ms(temp));	
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
	(void)c;
	if (str[i] == c)
	{
		ft_append(lex, str);
		return(0);
	}
	else
	{
		while (str[i] == ' ')
			i++;
		while ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '<') && (str[i] != '>'))
		{
			j++;
			i++;
		}
		if (j == 1)
			return (-1);
		temp = ft_substr(str, 0, i);
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp));		
	}
	return (i);
	
}

int	ft_lexer(t_ms *lex, char *str)
{
	int	i;
	int	j;
	int	res;
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
			ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp));
			i += j + 1;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			
			res = ft_chevron(&lex, str + i, str[i]);
			i += res;
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
			ft_lstadd_back_ms(&lex, ft_lstnew_ms("|"));
			i++;
		}
		else if (str[i] == ' ')
			i++;
		else
		{
			j = i;
			while ((str[j] != ' ') && (str[j] != '\0') && (str[j] != '<') && (str[j] != '>') && (str[j] != '|'))
				j++;
			temp = ft_substr(str + i, 0, j);
			ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp));
			i += j;
		}
		// i++;
	}
	ft_view_lst(lex);
	return (1);
}
	