/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_hexa_x_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:06:07 by amanasse          #+#    #+#             */
/*   Updated: 2022/06/02 18:11:28 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_hexa_x_x(unsigned int nb)
{
	unsigned int	n;
	int				i;

	n = nb;
	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 16;
		i++;
	}
	return (i);
}
