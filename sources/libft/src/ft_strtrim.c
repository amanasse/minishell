/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:32:27 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:34:55 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count(char const *str2, char const c)
{
	int	i;

	i = 0;
	while (str2[i])
	{
		if (str2[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	k = 0;
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] != '\0' && count(set, s1[i]) == 1)
		i++;
	while (j > 0 && count(set, s1[j - 1]) == 1)
	{
		j--;
		k++;
	}
	str = ft_substr(s1, i, ft_strlen(s1 + i) - k);
	return (str);
}
/*
int main()
{
	char str1[] = "coucoucLESouGARScoucou";
	char str2[] = "cou";

	printf("%s\n", ft_strtrim(str1, str2));

	return 0;
}
*/