/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:54:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/28 15:44:06 by mede-sou         ###   ########.fr       */
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

int	ft_check_quotes(char *str, char c)
{
	int	i;
	
	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i - 1);
		i++;
	}
	return (0);
}

int	ft_lexer(t_ms *lex, char *str2)
{
	int	i;
	int	j;
	char	*temp;

	i = 0;
	while (str2[i])
	{
		if (str2[i] == '\'' || str2[i] == '"')
		{			
			j = ft_check_quotes(str2 + i, str2[i]);
			if (j == 0)
				return (0);
			temp = ft_strncpy(str2 + i + 1, j);
			ft_lstadd_back_ms(&lex, ft_lstnew_ms(temp));
			i += j + 2;
		}
		i++;
	}
	return (1);
}
	