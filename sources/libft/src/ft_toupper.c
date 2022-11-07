/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:53:03 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:35:01 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c = c - 32;
	return (c);
}
/*
int main()
{
	int a;
	a = 98;
	printf("%d\n", toupper(a));
	printf("%d\n", ft_toupper(a));
	return 0;
}
*/
