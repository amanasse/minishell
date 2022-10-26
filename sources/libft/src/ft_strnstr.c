/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:19:58 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:34:25 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*str1;
	char	*str2;

	i = 0;
	str1 = (char *) big;
	str2 = (char *) little;
	if (!big)
		return (NULL);
	if (!little || ft_strlen(little) == 0)
		return ((char *)big);
	if (ft_strlen(little) > len)
		return (NULL);
	while (str1[i] != '\0')
	{
		if (i + ft_strlen(str2) > len)
			return (NULL);
		if (ft_strncmp(str1 + i, str2, ft_strlen(str2)) == 0)
			return (str1 + i);
		i++;
	}
	return (NULL);
}
/*
int main ()
{
	char str1[] = "Salut le";
	char str2[] = "le";
	int i = 7;

	printf("%s\n", ft_strnstr(str1, str2, sizeof(char) * i));
	//printf("%s\n", strnstr(str1, str2, sizeof(char) * i));


	return 0;
}
*/