/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:52:08 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/25 16:40:53 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace_dollar(char *str, char *new_str, t_minishell *minishell)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = ft_replace_var(str, minishell);
	tmp2 = NULL;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '"' 
		&& str[i] != '\'')
		i++;
	if (new_str != NULL)
		tmp2 = ft_strjoin(new_str, ft_strncpy(tmp, ft_strlen(tmp)));
	else
		tmp2 = ft_strncpy(tmp, ft_strlen(tmp));
	return (free(new_str), free(tmp), tmp2);
}

char	*ft_replace_var(char *str, t_minishell *minishell)
{
	int		i;
	char 	*value;
	char	*to_replace;
	char	*tmp_str;

	i = 0;
	tmp_str = NULL;
	to_replace = NULL;
	value = NULL;
	if (str[i] == '$')
	{
		if (str[i + 1] == '?')
			value = ft_itoa(minishell->shell.status);
		while (str[i] != ' ' && str[i] != '\0' && str[i] != '"' 
		&& str[i] != '\'')
			i++;
		if (!value)
		{
			to_replace = ft_substr(str, 1, i - 1);
			if (to_replace == NULL)
				return (NULL);
			value = getenv(to_replace);
		}
		if (value == NULL)
			value = "";
		if (!tmp_str)
			tmp_str = ft_strdup(value);
		else
			tmp_str = ft_strjoin(tmp_str, value);
		if (tmp_str == NULL)
			return (free(to_replace), NULL);
	}
	else
		return (str);
	return (free(to_replace), tmp_str);
}

int	ft_clean_lst(t_minishell *minishell)
{
	t_lstms	*temp;
	int		count;
	int		i;

	i = 0;
	temp = minishell->lstms;
	count = 0;
	// printf("temp = %p\n", temp);

	// if (temp->type == HEREDOC)
	// {
	// 	minishell->heredoc = 1;
	// printf("ms->heredoc = %d\n", minishell->heredoc);
	// }
	while (temp != NULL)
	{
		if (temp->type == QUOTES || temp->type == STRING
			|| temp->type == REDIR_L || temp->type == REDIR_R
			|| temp->type == APPEND)
			temp->str = ft_clean_if_quotes(temp->str, minishell);
		else if (temp->type == S_QUOTES)
			temp->str = ft_clean_simple_quotes(temp->str);
		else if (temp->type == PIPE)
			count++;
		temp = temp->next;
		i++;
	}
	return (count);
}
