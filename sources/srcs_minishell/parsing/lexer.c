/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:54:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/07 11:22:36 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lexer_quotes(int i, char *str, t_minishell *mini)
{
	char	*temp;
	int		j;

	j = i + 1;
	while (str[j] != str[i])
		j++;
	while (char_is_space(str[j]) == 0 && str[j] != '\0')
	{
		j++;
		if (str[j] == str[i])
		{
			j++;
			while (str[j] != str[i] && str[j] != '\0')
				j++;
		}
	}
	temp = ft_strncpy(str + i, j - i);
	if (temp == NULL)
		return (free(temp), -1);
	if (str[i] == '"')
		ft_lstadd_back_ms(&mini->lstms, ft_lstnew_ms(temp, QUOTES));
	else
		ft_lstadd_back_ms(&mini->lstms, ft_lstnew_ms(temp, S_QUOTES));
	return (j);
}

int	ft_lexer_others(int i, char *str, t_minishell *mini)
{
	char	*temp;
	int		j;

	j = i;
	while ((char_is_separator(str[j]) == 0) && (char_is_space(str[j]) == 0)
		&& (str[j] != '\0'))
		j++;
	temp = ft_substr(str + i, 0, j - i);
	if (temp == NULL)
		return (free(temp), -1);
	ft_lstadd_back_ms(&mini->lstms, ft_lstnew_ms(temp, STRING));
	return (j);
}

int	check_errors_before_lexer(char *str)
{
	if (str && check_if_quotes_are_closed(str, -1) == 0)
		return (printf("%s\n", ERR_SYNTAX), -1);
	else if (str && (str[0] == '|' || str[0] == '>' || str[0] == '<')
		&& str[1] == '\0')
		return (printf("%s '%c'\n", ERR_TOK, str[0]), -1);
	else if (str && (str[0] == '<' && str[1] == '<') && str[2] == '\0')
		return (printf("%s '%c%c'\n", ERR_TOK, str[0], str[1]), -1);
	return (0);
}

static int	ft_lexer_pipe(t_minishell *mini, char *str, int i)
{
	i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (-1);
	ft_lstadd_back_ms(&mini->lstms, ft_lstnew_ms("|", PIPE));
	return (i);
}

int	ft_lexer(t_minishell *m, char *s, int i)
{
	if (s && (check_errors_before_lexer(s) == -1))
		return (0);
	while (s && s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
			i = ft_lexer_quotes(i, s, m);
		else if (s[i] == '<' || s[i] == '>')
		{
			m->j = i;
			i = ft_lexer_redirection(i, s, m);
			if (i == -1)
				return (m->error = 1, printf("%s '%c'\n", ERR_TOK, s[m->j]), 0);
		}
		else if (s[i] == '|')
		{
			i = ft_lexer_pipe(m, s, i);
			if (i == -1)
				return (m->error = 1, printf("%s '%c'\n", ERR_TOK, s[0]), -1);
		}
		else if (s[i] == ' ')
			i++;
		else
			i = ft_lexer_others(i, s, m);
	}
	return (1);
}
