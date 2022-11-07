/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:18:48 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/07 13:48:45 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	lendest;
	size_t	lensrc;

	i = 0;
	lendest = ft_strlen(dst);
	lensrc = ft_strlen(src);
	j = lendest + lensrc;
	if (size <= lendest)
		return (lensrc + size);
	while (src[i] && lendest + i < size - 1)
	{
		dst[lendest + i] = src[i];
		i++;
	}
	dst[lendest + i] = '\0';
	return (j);
}

/*
int	main(void)
{
	
	char dest[30]; 
	char dest2[30]; 
	memset(dest, 0, 30);
	memset(dest2, 0, 30);
	char * src = (char *)"AAAAAAAAA";
	char * src2 = (char *)"AAAAAAAAA";
	dest[0] = 'B';
	dest2[0] = 'B';
	printf("ft_strlcat = %ld\n", ft_strlcat(dest, src, 15));
	printf("strlcat = %ld\n", strlcat(dest2, src2, 15));

	printf("dest  = %s\n", dest);
	printf("dest2 = %s\n", dest2);



	return 0;
}
*/