/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tmp_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:19:20 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/07 11:14:08 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_a_quote(int quote)
{
	if (quote == 0)
		quote = 1;
	else
		quote = 0;
	return (quote);
}

char	*ft_clean_simple_quotes(char *str, t_minishell *ms, int i, int j)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new_str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && ms->d_quote == 0)
			ms->s_quote = in_a_quote(ms->s_quote);
		else if (str[i] == '"' && ms->s_quote == 0)
			ms->d_quote = in_a_quote(ms->d_quote);
		else
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (free(str), new_str);
}

int	ft_str_is_dollar(t_minishell *ms, char *str, int i)
{
	if (str[0] == '$' && str[i + 1] == '\0')
	{
		if (ms->new_str)
			free(ms->new_str);
		ms->new_str = malloc(sizeof(char) * 2);
		ms->new_str[0] = '$';
		ms->new_str[1] = '\0';
		return (-1);
	}
	ms->new_str = ft_replace_dollar(str + i, ms->new_str, ms);
	i = while_char_is_caract(str, i);
	return (i);
}

char	*ft_clean_temp_str(char *str, t_minishell *ms, int i)
{
	ms->new_str = NULL;
	while (str[i])
	{
		if (str[i] == '"' && ms->s_quote == 0)
			ms->d_quote = in_a_quote(ms->d_quote);
		else if (str[i] == '\'')
		{
			if (ms->d_quote == 1)
				ms->new_str = ft_stock_str(ms->new_str, str[i]);
			else
				ms->s_quote = in_a_quote(ms->s_quote);
		}
		else if (str[i] == '$' && str[i + 1] != '$')
		{
			i = ft_str_is_dollar(ms, str, i);
			if (i == -1)
				return (free(str), ms->new_str);
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
	minishell->d_quote = 0;
	minishell->s_quote = 0;
	temp = minishell->lstms;
	count = 0;
	while (temp != NULL)
	{
		if (temp->type == QUOTES || temp->type == STRING
			|| temp->type == REDIR_L || temp->type == REDIR_R
			|| temp->type == APPEND)
			temp->str = ft_clean_temp_str(temp->str, minishell, 0);
		else if (temp->type == S_QUOTES)
			temp->str = ft_clean_simple_quotes(temp->str, minishell, 0, 0);
		else if (temp->type == PIPE)
			count++;
		temp = temp->next;
		i++;
	}
	return (count);
}
