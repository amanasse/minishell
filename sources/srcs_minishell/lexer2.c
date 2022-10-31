/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:54:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/31 10:36:12 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*prio ' ' et " " : verifier si fermes, sinon erreur OK
chaque maillon = 1 mot (split espace)
types :
1 = cmd
2 = pipe
3 = redirection entree < OK 
4 = redirection sortie > OK
5 = redirection << (append) doit recevoir un delimiteur
6 = redirection sortie append (reecrit dessus) >>
7 = var environnement $var
*/

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
	char	*temp;

	i = 1;
	(void)c;
	// if (str[i + 1] == c)
		// ft_append();
	// else
	// {
		while (str[i] == ' ')
			i++;
		while ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '<') && (str[i] != '>'))
			i++;
		temp = ft_substr(str, 0, i);
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp));
	// }
	return (1);
	
}

int	ft_lexer(t_ms *lex, char *str)
{
	int	i;
	int	j;
	char	*temp;

	i = 0;
	while (str[i])
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
		if (str[i] == '<' || str[i] == '>')
			ft_chevron(&lex, str + i, str[i]);
		i++;
	}
	ft_view_lst(lex);
	return (1);
}
	