/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:54:49 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:33:03 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	i = 0;
	d = dest;
	s = src;
	if (d < s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (dest);
}
/*
int main()
{
	char str[] = "ABCDEFGHIJKL";
	//char str2[] = "aaaaa";
	char str3[] = "ABCDEFGHIJKL";
	//char str4[] = "aaaaa";
	size_t n;

	n = 2;

	printf("%p\n", memmove(str + 3, str, sizeof(char) * n));
	printf("%s\n", str);
	printf("%p\n", ft_memmove(str3 + 3, str3, sizeof(char) * n));
	printf("%s\n", str3);

	return (0);
}
*/
