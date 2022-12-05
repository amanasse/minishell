/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tmp_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:19:20 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/05 12:26:39 by amanasse         ###   ########.fr       */
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

char	*ft_clean_simple_quotes(char *str, t_minishell *minishell, int i)
{
	char	*new_str;
	int		j;

	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new_str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			minishell->quote = in_a_quote(minishell);
			i++;
		}
		else if (str[i] == '"' && minishell->quote == 0)
			i++;
		else
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
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
	return (free(old_str), old_str = NULL, new_str);
}

char	*ft_clean_temp_str(char *str, t_minishell *ms, int i)
{
	ms->new_str = NULL;
	while (str[i])
	{
		if (str[i] == '"')
			ms->quote = in_a_quote(ms);
		else if (str[i] == '\'')
		{
			if (ms->quote == 1)
				ms->new_str = ft_stock_str(ms->new_str, str[i]);
		}
		else if (str[i] == '$' && str[i + 1] != '$')
		{
			if (str[0] == '$' && str[i + 1] == '\0')
				return (free(str), free(ms->new_str), "$");
			ms->new_str = ft_replace_dollar(str + i, ms->new_str, ms);
			i = while_char_is_caract(str, i);
		}
		else
			ms->new_str = ft_stock_str(ms->new_str, str[i]);
		i++;
	}
	if (ms->new_str == NULL)
		ms->new_str = ft_malloc(1);
	return (free(str), str = NULL, ms->new_str);
}

int	ft_clean_lst(t_minishell *minishell)
{
	t_lstms	*temp;
	int		count;
	int		i;

	i = 0;
	minishell->quote = 0;
	temp = minishell->lstms;
	count = 0;
	while (temp != NULL)
	{
		if (temp->type == QUOTES || temp->type == STRING
			|| temp->type == REDIR_L || temp->type == REDIR_R
			|| temp->type == APPEND)
			temp->str = ft_clean_temp_str(temp->str, minishell, 0);
		else if (temp->type == S_QUOTES)
			temp->str = ft_clean_simple_quotes(temp->str, minishell, 0);
		else if (temp->type == PIPE)
			count++;
		temp = temp->next;
		i++;
	}
	return (count);
}
