/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:19:20 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/09 12:19:44 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"
#include "../../../includes/minishell.h"

char	*ft_clean_simple_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (new_str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			i++;
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);	
}

char	*ft_stock_str(char *old_str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc (ft_strlen(old_str) + 2);
	if (new_str == NULL)
		return (NULL);
	while (old_str && old_str[i])
	{
		new_str[i] = old_str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (new_str);
}

char	*ft_clean_if_quotes(char *str)
{
	int		i;
	int		quote;
	char	*tmp2;
	char	*new_str;
	
	i = 0;
	quote = 0;
	tmp2 = NULL;
	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (quote == 0)
				quote = 1;
			i++;
		}
		else if (str[i] == '\'')
		{
			if (quote == 1)
				new_str = ft_stock_str(new_str, str[i]);
			i++;
		}
		else if (str[i] == '$')
		{
			tmp2 = ft_replace_var(str + i);
			while (str[i] != ' ' && str[i] != '\0' && str[i] != '"' && str[i] != '\'')
				i++;
			if (new_str)
				new_str = ft_strcat(new_str, ft_strncpy(tmp2, ft_strlen(tmp2)));
			else
				new_str = ft_strncpy(tmp2, ft_strlen(tmp2));
		}
		else
		{
			new_str = ft_stock_str(new_str, str[i]);
			i++;
		}
	}
	if (new_str == NULL)
	{
		new_str = malloc(sizeof(char));
		new_str[0] = '\0';
	}
	return (new_str);
}
