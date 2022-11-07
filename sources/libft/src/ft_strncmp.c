/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:02:48 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:34:25 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			j;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	j = 0;
	if (n == 0)
		return (0);
	while (j == 0 && i < n)
	{
		j = str1[i] - str2[i];
		if (str1[i] == '\0' && str2[i] == '\0')
			break ;
		i++;
	}
	return (j);
}

/*
int main()
{
	char str1[] = "test";
	char str2[] = "testss";
	int n = 7;
	printf("%d\n", strncmp(str1, str2, n));
	printf("%d\n", ft_strncmp(str1, str2, n));

    return 0;
}
*/