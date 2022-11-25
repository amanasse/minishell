/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:54:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/25 16:54:25 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_quotes_are_closed(char *str)
{
	int	i;
	int	in_s_quotes;
	int	in_d_quotes;

	i = 0;
	in_s_quotes = 0;
	in_d_quotes = 0;
	while (str[i] && str)
	{
		if (str[i] == '\'')
		{
			if ((in_s_quotes == 0 && in_d_quotes == 1) || (in_s_quotes == 1))
				in_s_quotes = 0;
			else
				in_s_quotes = 1;
		}
		if (str[i] == '"')
		{
			if ((in_d_quotes == 0 && in_s_quotes == 1) || (in_d_quotes == 1))
				in_d_quotes = 0;
			else
				in_d_quotes = 1;
		}
		i++;
	}
	if (in_s_quotes == 0 && in_d_quotes == 0)
		return (1);
	return (0);
}

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
		return (free(temp), 0);
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
		return (free(temp), 0);
	ft_lstadd_back_ms(&mini->lstms, ft_lstnew_ms(temp, STRING));
	return (j);
}

int	check_errors_before_lexer(char *str)
{
	if (str && check_if_quotes_are_closed(str) == 0)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), -1);
	else if (str && (str[0] == '|' || str[0] == '>' || str[0] == '<') && str[1] == '\0')
		return (printf("minishell: syntax error near unexpected token '%c'\n", str[0]), -1);
	else if (str && (str[0] == '<' && str[1] == '<') && str[2] == '\0')
		return (printf("minishell: syntax error near unexpected token '%c%c'\n", str[0], str[1]), -1);
	return (0);
}

int	ft_lexer(t_minishell *minishell, char *str)
{
	int		i;

	i = 0;
	if (str && (check_errors_before_lexer(str) == -1))
		return (0);
	while (str && str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')	
			i = ft_lexer_quotes(i, str, minishell);
		else if (str[i] == '<' || str[i] == '>')
		{
			i = ft_lexer_redirection(i, str, minishell);
			if (i == -1)	
				return (printf("%s '%c'\n", ERR_CHEVRON, str[i]), 0);			
		}
		else if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '|')
				return (printf("minishell: syntax error near unexpected token `|'\n"), -1);
			ft_lstadd_back_ms(&minishell->lstms, ft_lstnew_ms("|", PIPE));
		}
		else if (str[i] == ' ')
			i++;
		else
			i = ft_lexer_others(i, str, minishell);
	}
	return (1);
}

