/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:14:16 by amanasse          #+#    #+#             */
/*   Updated: 2022/06/01 16:20:56 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_hexa(unsigned long long nb)
{
	int				i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}
