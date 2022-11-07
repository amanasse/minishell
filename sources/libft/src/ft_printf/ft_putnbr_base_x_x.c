/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_x_x.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:11:35 by amanasse          #+#    #+#             */
/*   Updated: 2022/06/15 19:10:07 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base_x_x(unsigned int nb, char *base)
{
	if (nb >= (unsigned int)ft_strlen(base))
	{
		ft_putnbr_base_x_x(nb / ft_strlen(base), base);
		ft_putnbr_base_x_x(nb % ft_strlen(base), base);
	}
	else
		write (1, &base[nb], 1);
}
