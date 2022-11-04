/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:52:08 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/04 18:13:52 by mede-sou         ###   ########.fr       */
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

char	*ft_replace_var(t_ms *temp)
{
	int		i;
	int		j;
	char 	*value;
	char	*to_replace;
	char	*tmp_str;

	i = 0;
	tmp_str = NULL;
	while (temp->str[i] != '$' && temp->str[i] != '\0')
		i++;
	if (temp->str[i] == '$')
	{
		if (i > 0)
		{
			tmp_str = ft_substr(temp->str, 0, i);
			if (tmp_str == NULL)
				return (NULL);
		}
		j = i;
		while (temp->str[j] != ' ' && temp->str[j] != '\0' && temp->str[j] != '"')
			j++;
		to_replace = ft_substr(temp->str + i, 1, j);
		if (to_replace == NULL)
			return (NULL);
		value = getenv(to_replace);
		if (value == NULL)
			value = "";
		if (!tmp_str)
			tmp_str = ft_strdup(value);
		else
			tmp_str = ft_strcat(tmp_str, value);
		if (temp->str[j + 1] != '\0')
			tmp_str = ft_strcat(tmp_str, temp->str + j);
	}
	else
		return (temp->str);
	return (tmp_str);
}

char	*ft_clean_quotes(t_ms *temp)
{
	int		i;
	int		j;
	char	*tmp_str;
	
	i = 1;
	j = 0;
	while (temp->str[i] != '\0' && temp->str[i] != '"')
		i++;
	tmp_str = ft_substr(temp->str, 1, ft_strlen(temp->str) - 2);
	if (tmp_str == NULL)
		return (NULL);
	i = 0;
	while (tmp_str[i])
	{
		if (tmp_str[i] == '"')
		{
			j = i + 1;
			while (tmp_str[j] != '"' && tmp_str[j] != '\0')
				j++;
			tmp_str = ft_strcat(tmp_str, tmp_str + i);
			printf("tmp_str = %s\n", tmp_str);
		}
		i++;
	}
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
			temp->str = ft_replace_var(temp);
		else if (temp->type == 8)
			temp->str = ft_clean_simple_quotes(temp);
		temp = temp->next;
	}
	// ft_join_maillons(lex);
}


// void	ft_join_maillons(t_ms **lex)
// {
// 	t_ms	*temp;

// 	temp = *lex;
// 	while (temp->next != NULL)
// 	{
// 		if (temp->type == 0)
// 		{
// 			if ((temp->next->type == 1 || temp->next->type == 1) && temp->next != NULL)
// 			{
// 				temp->str = ft_strcat(temp->str, temp->next->str);
// 				temp->next = temp->next->next;
// 				temp->type = 1;
// 				if (temp->next == NULL)
// 					break ;
// 			}
// 			else
// 				temp = temp->next;
// 		}
// 		else if (temp->type == 1)
// 		{
// 			if (temp->next->type == 0 && temp->next != NULL)
// 			{
// 				temp->str = ft_strcat(temp->str, temp->next->str);
// 				temp->next = temp->next->next;
// 				if (temp->next == NULL)
// 					break ;
// 			}
// 			else
// 				temp = temp->next;
// 		}
// 		else
// 			temp = temp->next;
// 	}
// }