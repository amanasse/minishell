/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:52:08 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/07 12:12:17 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
0 = entre guillemets "" OK
1 = cmd - str OK
2 = pipe　OK
3 = redirection entree < OK
4 = redirection sortie > OK
5 = redirection << (append) doit recevoir un delimiteur OK
6 = redirection sortie append (reecrit dessus) >> OK
7 = var environnement $var
fonction a faire = check si caractere est valide apres $ // ex : @ - = # & *
8 = entre ''
 */

char	*ft_clean_simple_quotes(t_ms *temp)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(temp->str) - 1));
	if (str == NULL)
		return (NULL);
	while (temp->str[i])
	{
		if (temp->str[i] == '\'')
			i++;
		str[j] = temp->str[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);	
}

char	*ft_replace_var(char *str)
{
	int		i;
	int		j;
	char 	*value;
	char	*to_replace;
	char	*tmp_str;

	i = 0;
	tmp_str = NULL;
	while (str[i] != '$' && str[i] != '\0')
		i++;
	if (str[i] == '$')
	{
		if (i > 0)
		{
			tmp_str = ft_substr(str, 0, i);
			if (tmp_str == NULL)
				return (NULL);
		}
		j = i;
		while (str[j] != ' ' && str[j] != '\0')
			j++;
		to_replace = ft_substr(str + i, 1, j);
		if (to_replace == NULL)
			return (NULL);
		value = getenv(to_replace);
		if (value == NULL)
			value = "";
		if (!tmp_str)
			tmp_str = ft_strdup(value);
		else
			tmp_str = ft_strcat(tmp_str, value);
	}
	else
		return (str);
	return (tmp_str);
}

char	*ft_clean_quotes(t_ms *temp)
{
	int		i;
	int		j;
	int		k;
	char	*tmp_str;
	char	*tmp2;
	
	i = 1;
	k = 0;
	tmp2 = NULL;
	while (temp->str[i] != '\0' && temp->str[i] != '"' && temp->str[i] != '$')
		i++;
	tmp_str = ft_substr(temp->str, 1, ft_strlen(temp->str) - 2);
	if (tmp_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (tmp_str[i])
	{
		if (tmp_str[i] == '"')
			i++;
		else if (tmp_str[i] == '$')
		{
			tmp2 = ft_replace_var(tmp_str + i);
			while (tmp_str[i] != ' ' && tmp_str[i] != '\0' && tmp_str[i] != '"')
				i++;
			while (tmp2[k])
			{
				tmp_str[j] = tmp2[k];
				j++;
				k++;
			}
		}
		else
		{
			tmp_str[j] = tmp_str[i];
			j++;
			i++;
		}
	}
	tmp_str[j] = '\0';
	return (tmp_str);
}

void	ft_clean_lst(t_ms **lex)
{
	t_ms	*temp;

	temp = *lex;
	while (temp != NULL)
	{
		if (temp->type == 0)
			temp->str = ft_clean_quotes(temp);
		else if (temp->type == 1)
			temp->str = ft_replace_var(temp->str);
		else if (temp->type == 8)
			temp->str = ft_clean_simple_quotes(temp);
		temp = temp->next;
	}
}
