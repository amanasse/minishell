/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:15:14 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:32:51 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	d;

	str = (unsigned char *) s;
	d = (unsigned char) c;
	i = 0;
	if (!s || n > 256)
		return (NULL);
	while (i < n)
	{
		if (str[i] == d)
			return (str + i);
		i++;
	}
	return (NULL);
}
/*
int main()
{
	char str1[] = "Bonnour les mecj";
	char str2[] = "Bonnour les mecj";
	int i = 122;
	int n = 250;
	printf("%p\n", (char *)memchr(str1, i, n));
	printf("%p\n", (char *)ft_memchr(str2, i, n));

	return 0;
}
*/