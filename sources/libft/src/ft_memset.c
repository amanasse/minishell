/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:02:02 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:33:07 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

/*
int	main ()
{
	int tab[] = {50, 10, 20, 5, 100};
	int tab2[] = {50, 10, 20, 5, 100};
	char str[] = "Coucou les gars ca va ?";
	char str2[] = "Coucou les gars ca va ?";
	
	int c;
	c = 1;
	size_t n;
	n = 3;
	printf("%p\n", memset (tab, c, sizeof(int)*n));
	//printf("%d\n", str);
	
	printf("%d\n", tab[0]);
	printf("%d\n", tab[1]);
	printf("%d\n", tab[2]);
	printf("%d\n", tab[3]);
	printf("%p\n",ft_memset (tab2, c, sizeof(int)*n));
	//printf("%s\n", str2);
	printf("%d\n", tab2[0]);
	printf("%d\n", tab2[1]);
	printf("%d\n", tab2[2]);
	printf("%d\n", tab2[3]);

	return 0;
}
*/
