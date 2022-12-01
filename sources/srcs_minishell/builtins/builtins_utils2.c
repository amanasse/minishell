/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:54:52 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/01 17:23:34 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

char	*ft_strcpy_egal(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '=';
	i++;
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy_concataine(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] && src[i] != '+')
	{
		i++;
	}
	dest = malloc(sizeof(char) * i + 2);
	i = 0;
	while (src[i] != '+')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '=';
	i++;
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
