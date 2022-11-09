/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:54:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/09 17:48:26 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"
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

int	check_if_quotes_are_closed(char *str)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quotes++;
		if (str[i] == '"')
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 == 0 && double_quotes % 2 == 0)
		return (1);
	return (0);
}

int	ft_lexer_quotes(int i, char *str, t_ms **lex)
{
	char	*temp;
	int		j;

	j = i + 1;
	while (str[j] != str[i])
		j++;
	while (char_is_space(str[j]) == 0 && str[j] != '\0')
		j++;
	temp = ft_strncpy(str + i, j - i);
	if (temp == NULL)
		return (0);
	if (str[i] == '"')
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 0));
	else
		ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 8));
	return (j);
}

int	ft_lexer_others(int i, char *str, t_ms **lex)
{
	char	*temp;
	int		j;

	j = i;
	while ((char_is_separator(str[j]) == 0) && (char_is_space(str[j]) == 0)
		&& (str[j] != '\0'))
		j++;
	temp = ft_substr(str + i, 0, j - i);
	if (temp == NULL)
		return (0);
	ft_lstadd_back_ms(lex, ft_lstnew_ms(temp, 1));
	return (j);
}

int	ft_lexer_redirection(int i, char *str, t_ms **lex)
{
	int	res;
	
	res = ft_chevron(lex, str + i, str[i]);
	i += res;
	if (res == 0)
		i++;
	else if (res == -1)	
		return (-1);
	return (i);
}

int	ft_lexer(t_ms *lex, char *str)
{
	int		i;

	i = 0;
	if (check_if_quotes_are_closed(str) == 0)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')	
			i = ft_lexer_quotes(i, str, &lex);
		else if (str[i] == '<' || str[i] == '>')
		{
			i = ft_lexer_redirection(i, str, &lex);
			if (i == -1)	
				return (printf("%s '%c'\n", ERR_CHEVRON, str[i]), 0);
		}
		else if (str[i] == '|')
		{
			ft_lstadd_back_ms(&lex, ft_lstnew_ms("|", 2));
			i++;
		}
		else if (str[i] == ' ')
			i++;
		else
			i = ft_lexer_others(i, str, &lex);
	}
	ft_view_lst(lex); // a supprimer
	ft_clean_lst(&lex); // a supprimer
	return (1);
}

