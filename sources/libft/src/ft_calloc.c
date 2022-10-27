/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:31:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:31:20 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char		*str;
	size_t		i;

	if (nmemb != 0 && size != 0)
	{
		if (nmemb * size / size != nmemb)
			return (NULL);
	}
	i = 0;
	str = (void *)malloc(nmemb * size);
	if (str == NULL)
		return (NULL);
	while (i < (nmemb * size))
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
/*
	int main()
{
	printf("%p\n", ft_calloc(__SIZE_MAX__/2 +1, __SIZE_MAX__/2 +1));
	printf("%p\n", calloc(__SIZE_MAX__/2 + 1, __SIZE_MAX__/2 +1));
	return 0;
}
*/