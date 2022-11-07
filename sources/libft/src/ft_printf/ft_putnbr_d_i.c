/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_d_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:10:33 by amanasse          #+#    #+#             */
/*   Updated: 2022/05/31 19:08:08 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_d_i(int n)
{
	int	i;
	int	ok;

	ok = 0;
	i = count_nb(n);
	if (n < 0)
	{
		n *= -1;
		ft_putchar('-');
	}
	if (n == -2147483648)
	{
		ok = 1;
		write(1, "2147483648", 10);
	}
	else if (n < 10)
	{
		ft_putchar(n + 48);
		ok = 1;
	}
	else
		ft_putnbr_d_i(n / 10);
	if (ok == 0)
		ft_putchar((n % 10) + 48);
	return (i);
}
