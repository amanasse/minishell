/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:54:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/30 14:56:27 by mede-sou         ###   ########.fr       */
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
		j++;
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
		return (printf("%s '%c'\n", ERR_SY_TOK, str[0]), -1);
	else if (str && (str[0] == '<' && str[1] == '<') && str[2] == '\0')
		return (printf("%s '%c%c'\n", ERR_SY_TOK, str[0], str[1]), -1);
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

int	ft_lexer(t_minishell *minishell, char *str, int i)
{
	int	j;

	if (str && (check_errors_before_lexer(str) == -1))
		return (0);
	while (str && str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			i = ft_lexer_quotes(i, str, minishell);
		else if (str[i] == '<' || str[i] == '>')
		{
			j = i;
			i = ft_lexer_redirection(i, str, minishell);
			if (i == -1)
			{
				minishell->error = 1;
				return (printf("%s '%c'\n", ERR_SY_TOK, str[j]), 0);
			}
		}
		else if (str[i] == '|')
		{
			i = ft_lexer_pipe(minishell, str, i);
			if (i == -1)
			{
				minishell->error = 1;
				return (printf("%s '%c'\n", ERR_SY_TOK, str[0]), -1);
			}
		}
		else if (str[i] == ' ')
			i++;
		else
			i = ft_lexer_others(i, str, minishell);
	}
	return (1);
}
