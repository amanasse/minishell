/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:02:29 by amanasse          #+#    #+#             */
/*   Updated: 2022/05/31 19:08:06 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_u(unsigned int n)
{
	int	ok;

	ok = 0;
	if (n < 10)
	{
		ft_putchar(n + 48);
		ok = 1;
	}
	else
		ft_putnbr_u(n / 10);
	if (ok == 0)
		ft_putchar((n % 10) + 48);
}
