/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:30:33 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:34:25 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	d;

	i = 0;
	if (!s)
		return (NULL);
	d = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == d)
			return ((char *)s + i);
		i++;
	}
	if (d == 0)
		return ((char *)s + i);
	return (NULL);
}
/*
int main()
{
	char str[] = "Je suis la";
	
	int i = 105;
	char c = 98;

	printf("%s\n", ft_strchr(str, i));
	printf("%s\n", strchr(str, i));
	return (0);
}
*/
