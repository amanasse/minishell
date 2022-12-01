/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:52:08 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/01 11:23:43 by mede-sou         ###   ########.fr       */
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

char	*get_value_var(char *value, char *to_replace, char *str, int i)
{
	to_replace = ft_substr(str, 1, i);
	if (to_replace == NULL)
		return (NULL);
	value = getenv(to_replace);
	if (value == NULL)
		value = "";
	return (free(to_replace), value);
}

char	*ft_replace_var(char *str, t_minishell *minishell)
{
	int		i;
	char	*value;
	char	*to_replace;
	char	*tmp_str;

	i = 0;
	tmp_str = NULL;
	to_replace = NULL;
	value = NULL;
	if (str[i + 1] == '?')
	{
		value = ft_itoa(minishell->shell.status);
		return (free(to_replace), value);
	}
	i = while_char_is_caract(str, i);
	if (!value)
		value = get_value_var(value, to_replace, str, i);
	if (!tmp_str)
		tmp_str = ft_strdup(value);
	else
		tmp_str = ft_strjoin(tmp_str, value);
	if (tmp_str == NULL)
		return (free(to_replace), NULL);
	return (free(to_replace), tmp_str);
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
