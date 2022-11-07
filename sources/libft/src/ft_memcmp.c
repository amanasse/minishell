/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:38:56 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:32:55 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n)
	{	
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
	char str1[] = "Salut les boys";
	char str2[] = "Salut lea boyw";
	int tab[5] = {10, 2, 2, 50, 1};
	int tab2[5] = {10, 5, 2, 50, 1};
	int n = 3;
	printf("%d\n", memcmp(str1, str2, sizeof(char) * n));
	printf("%d\n", ft_memcmp(str1, str2, sizeof(char) * n));
	printf("%d\n", memcmp(tab, tab2, sizeof(int) * n));
	printf("%d\n", ft_memcmp(tab, tab2, sizeof(int) * n));
    return 0;
}
*/