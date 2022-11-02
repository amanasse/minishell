/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:16:31 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:32:03 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count(int nb)
{
	int	n;

	n = 0;
	if (nb == 0)
		return (1);
	if (nb == -2147483648)
		return (11);
	if (nb > -2147483648 && nb < 0)
	{
		nb = -nb;
		n++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		n++;
	}
	if (nb > 0 && nb < 10)
		n++;
	return (n);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			countnb;
	char		*str;
	int			neg;

	neg = 0;
	nb = n;
	countnb = count(nb);
	if (nb < 0 && --neg)
		nb = -nb;
	str = malloc(sizeof(char) * (countnb + 1));
	if (!str)
		return (NULL);
	str[countnb] = '\0';
	while (countnb > 0)
	{
		str[countnb - 1] = (nb % 10) + 48;
		nb = nb / 10;
		countnb--;
	}
	if (neg < 0)
		str[0] = '-';
	return (str);
}
/*
int main()
{

    int i = 542;
    printf("%s\n", ft_itoa(i));
   
    return (0);
}
*/