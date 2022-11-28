/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:19:20 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/28 13:34:35 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_a_quote(t_minishell *minishell)
{
	if (minishell->quote == 0)
		minishell->quote = 1;
	else
		minishell->quote = 0;
	return (minishell->quote);
}

char	*ft_clean_simple_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new_str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			i++;
		if (str[i] == '"' && str[i + 1] == '"')
			i += 2;
		// else if (str[i] == '"' && minishell->quote == 0)
		// 	i++;
		new_str[j] = str[i];
		if (str[i] == '\0')
			break ;
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (free(str), new_str);
}

char	*ft_stock_str(char *old_str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(sizeof(char) *(ft_strlen(old_str) + 2));
	if (new_str == NULL)
		return (NULL);
	while (old_str && old_str[i])
	{
		new_str[i] = old_str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (free(old_str), new_str);
}

char	*ft_malloc(int len)
{
	char	*s;

	s = malloc(sizeof(char) * len);
	if (s == NULL)
		return (NULL);
	s[0] = '\0';
	return (s);
}

char	*ft_clean_temp_str(char *str, t_minishell *minishell, int i)
{
	char	*new_str;

	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '"')
			minishell->quote = in_a_quote(minishell);
		else if (str[i] == '\'')
		{
			if (minishell->quote == 1)
				new_str = ft_stock_str(new_str, str[i]);
		}
		else if (str[i] == '$' && str[i + 1] != '$')
		{
			new_str = ft_replace_dollar(str + i, new_str, minishell);
			i = while_char_is_caract(str, i);
		}
		else
			new_str = ft_stock_str(new_str, str[i]);
		i++;
	}
	if (new_str == NULL)
		new_str = ft_malloc(1);
	return (free(str), new_str);
}
