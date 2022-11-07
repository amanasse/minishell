/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:35:00 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 16:44:44 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup_gnl(char *s)
{
	char	*str;
	int		i;

	i = ft_strlen_gnl(s);
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strlen_gnl(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	int		lens1;
	int		lens2;
	char	*str;

	lens1 = ft_strlen_gnl(s1);
	lens2 = ft_strlen_gnl(s2);
	str = malloc(sizeof(char) * ((lens1 + lens2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int	check_sep(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*stock_line_last(char *dest)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(sizeof(char) * (ft_strlen_gnl(dest) + 1));
	if (!line)
		return (NULL);
	while (dest[i] != '\0')
	{
		line[i] = dest[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
