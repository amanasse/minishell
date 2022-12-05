/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:52:08 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/05 14:09:44 by amanasse         ###   ########.fr       */
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
	if (tmp[0] == '\0' || tmp[0] == '$')
		return (new_str);
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

int	ft_init_get_value(t_minishell *m, char *s, int i)
{
	m->l = 0;
	m->get_value = NULL;
	m->replace = ft_substr(s, 1, i);
	m->t = m->environ;
	if (m->replace == NULL)
		return (-1);
	return (0);
}

char	*get_value_var(t_minishell *m, char *s, int i)
{
	if (ft_init_get_value(m, s, i) == -1)
		return (NULL);
	while (m->t)
	{
		if (ft_strncmp(m->t->str, m->replace, ft_strlen(m->replace)) == 0)
		{
			while (m->t->str[m->l] != '=' && m->t->str[m->l] != '\0')
				m->l++;
			if (m->t->str[m->l] == '=' && m->l == (int)ft_strlen(m->replace)
				&& m->t->str[m->l] != '\0')
			{
				m->get_value = ft_substr(m->t->str, m->l + 1,
						ft_strlen(m->t->str));
				if (m->get_value)
					return (free(m->replace), m->get_value);
			}
		}
		m->t = m->t->next;
	}
	if (m->get_value == NULL)
		m->get_value = "";
	return (free(m->replace), m->get_value);
}

char	*ft_replace_var(char *str, t_minishell *minishell)
{
	int		i;
	char	*tmp_str;

	i = 0;
	tmp_str = NULL;
	minishell->value = NULL;
	if (str[i + 1] == '?')
	{
		minishell->value = ft_itoa(minishell->shell.status);
		return (minishell->value);
	}
	i = while_char_is_caract(str, i);
	if (!minishell->value)
	{
		minishell->value = get_value_var(minishell, str, i);
		return (minishell->value);
	}
	if (!tmp_str)
		tmp_str = ft_strdup(minishell->value);
	else
		tmp_str = ft_strjoin(tmp_str, minishell->value);
	if (tmp_str == NULL)
		return (free(minishell->value), NULL);
	return (tmp_str);
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
