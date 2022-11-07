/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:23:07 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:32:58 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void	*dest, const void *src, size_t n)
{
	char		*str;
	const char	*str2;
	size_t		i;

	i = 0;
	str = dest;
	str2 = src;
	while (i < n)
	{
		str[i] = str2[i];
		i++;
	}
	return (dest);
}
/*
int main()
{
	char str[] = "coucoucestmoiahahah";
	char str2[] = "aaaaa";
	char str3[] = "coucoucestmoiahahah";
	char str4[] = "aaaaa";
	size_t n;

	n = 6;

	printf("%p\n", memcpy(str, str2, sizeof(char) * n));
	printf("%s\n", str);
	printf("%p\n", ft_memcpy(str3, str4, sizeof(char) * n));
	printf("%s\n", str3);

	return (0);
}
*/
