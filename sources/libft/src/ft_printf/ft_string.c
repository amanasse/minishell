/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:13:07 by amanasse          #+#    #+#             */
/*   Updated: 2022/05/31 15:39:52 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_string(char *str)
{
	if (str == NULL)
	{
		write (1, "(null)", 6);
		return (6);
	}
	else
	{
		write (1, str, ft_strlen(str));
		return (ft_strlen(str));
	}
}
