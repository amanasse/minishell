/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:39:25 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/07 12:26:36 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_malloc(int len)
{
	char	*s;

	s = malloc(sizeof(char) * len);
	if (s == NULL)
		return (NULL);
	s[0] = '\0';
	return (s);
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
