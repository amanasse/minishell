/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:11:44 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:34:57 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	d;

	i = 0;
	if (!s)
		return (NULL);
	d = (unsigned char) c;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == d)
			return ((char *) s + i);
		i--;
	}
	return (NULL);
}

/*
int main()
{
	char str[] = "i Je sus la  la";
	
	int i = 105;

	printf("%p\n", ft_strrchr(str, i));
	printf("%p\n", strrchr(str, i));
	return (0);
}
*/
