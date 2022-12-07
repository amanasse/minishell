/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:09:07 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/07 14:42:42 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append(t_minishell *mini, char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 2;
	while (str[i] == ' ')
		i++;
	j = i;
	while ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '<')
		&& (str[i] != '>'))
		i++;
	temp = ft_substr(str, j, i - j);
	if (temp == NULL)
		return (0);
	if (str[1] == '<')
		ft_lstadd_back_ms(&mini->lstms, ft_lstnew_ms(temp, HEREDOC));
	else if (str[1] == '>')
		ft_lstadd_back_ms(&mini->lstms, ft_lstnew_ms(temp, APPEND));
	return (i);
}

int	pass_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int	ft_chevron(t_minishell *mini, char *str, char c, int i)
{
	int		j;
	char	*temp;

	j = 1;
	if (str[i] == c)
	{
		if (str[i + 1] == '<' || str[i + 1] == '>')
			return (-1);
		return (ft_append(mini, str));
	}
	j = pass_spaces(str, j);
	i = pass_spaces(str, i);
	i++;
	while ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '<')
		&& (str[i] != '>'))
		i++;
	temp = ft_substr(str, j, i - j);
	if (temp == NULL)
		return (-1);
	if (c == '<')
		ft_lstadd_back_ms(&mini->lstms, ft_lstnew_ms(temp, REDIR_L));
	else if (c == '>')
		ft_lstadd_back_ms(&mini->lstms, ft_lstnew_ms(temp, REDIR_R));
	return (i);
}

int	ft_lexer_redirection(int i, char *str, t_minishell *mini)
{
	int	res;

	res = ft_chevron(mini, str + i, str[i], 1);
	i += res;
	if (res == 0)
		i++;
	else if (res == -1)
		return (-1);
	return (i);
}
