/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:52:08 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/07 15:44:47 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace_dollar(char *str, char *new_str, t_minishell *minishell)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	tmp = ft_replace_var(str, minishell);
	if (tmp && (tmp[0] == '\0' || tmp[0] == '$'))
		return (new_str);
	tmp2 = NULL;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '"'
		&& str[i] != '\'')
		i++;
	if (new_str != NULL)
	{
		tmp3 = new_str;
		tmp2 = ft_strjoin(new_str, tmp);
		free(tmp3);
	}
	else
		tmp2 = ft_strncpy(tmp, ft_strlen(tmp));
	return (free(tmp), tmp2);
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

char	*ft_construction_str(t_minishell	*minishell)
{
	char	*tmp;
	char	*str;

	str = NULL;
	if (!str)
		str = ft_strdup(minishell->value);
	else
	{
		tmp = str;
		str = ft_strjoin(str, minishell->value);
		free(tmp);
	}
	if (str == NULL)
		return (free(minishell->value), NULL);
	return (str);
}

char	*ft_replace_var(char *str, t_minishell *minishell)
{
	int		i;
	char	*tmp_str;

	i = 0;
	tmp_str = NULL;
	minishell->value = NULL;
	if (str[i + 1] == '\0')
		return (minishell->value);
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
	tmp_str = ft_construction_str(minishell);
	if (tmp_str == NULL)
		return (NULL);
	return (free(minishell->value), tmp_str);
}
