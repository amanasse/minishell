/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:52:08 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/22 12:21:01 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
0 = entre guillemets "" OK
1 = cmd - str OK
2 = pipe　OK
3 = redirection entree < OK
4 = redirection sortie > OK
5 = redirection << (append) doit recevoir un delimiteur OK
6 = redirection sortie append (reecrit dessus) >> OK
7 = var environnement $var
fonction a faire = check si caractere est valide apres $ // ex : @ - = # *
8 = entre ''
 */

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
		printf("value = %s\n", value);
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

	temp = minishell->lstms;
	count = 0;
	while (temp != NULL)
	{
		if (temp->type == 0 || temp->type == 1 || temp->type == 3
			|| temp->type == 4 || temp->type == 5 || temp->type == 6)
			temp->str = ft_clean_if_quotes(temp->str, minishell);
		else if ( temp->type == 8)
			temp->str = ft_clean_simple_quotes(temp->str);
		else if (temp->type == 2)
			count++;
		temp = temp->next;
	}
	return (count);
}
