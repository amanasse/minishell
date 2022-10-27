/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:47:44 by amanasse          #+#    #+#             */
/*   Updated: 2022/05/12 10:34:35 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
/*
int	main()
{
	int n;
	n = 4;
	char str[] = "Coucou les amis";
	
	char str2[] = "Coucou les amis";
	printf("%s\n", str);	
	printf("%s\n", str2);
	
	bzero(str + 5, n);
	ft_bzero(str2 + 5, n);
	printf("%s\n", str);
	printf("%s\n", str2);
	return 0;

}
*/
