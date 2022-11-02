/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:30:00 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 18:09:57 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_char_p(char c, va_list *ap)
{	
	unsigned long long	tmp;
	int					count;

	count = 0;
	if (c == 'p')
	{
		tmp = (unsigned long long)va_arg(*ap, void *);
		if (tmp == 0)
		{	
			write (1, "(nil)", 5);
			count += 5;
		}
		else
		{
			write (1, "0x", 2);
			count += 2;
			count += count_hexa(tmp);
			ft_putnbr_base(tmp, "0123456789abcdef");
		}
	}
	return (count);
}

int	ft_check_char_scdup(char c, va_list *ap)
{
	unsigned int	tmp;
	int				count;

	count = 0;
	if (c == 's')
		count += ft_string(va_arg(*ap, char *));
	if (c == 'c')
		count += ft_char(va_arg(*ap, int));
	if (c == 'd' || c == 'i')
		count += ft_putnbr_d_i(va_arg(*ap, int));
	if (c == 'u')
	{
		tmp = (unsigned int)va_arg(*ap, unsigned int);
		count += count_u(tmp);
		ft_putnbr_u(tmp);
	}
	return (count);
}

int	ft_check_char(char c, va_list *ap)
{
	long long	tmp;
	int			count;

	count = 0;
	count += ft_check_char_scdup (c, ap);
	count += ft_check_char_p (c, ap);
	if (c == 'x')
	{
		tmp = va_arg(*ap, int);
		count += count_hexa_x_x(tmp);
		ft_putnbr_base_x_x(tmp, "0123456789abcdef");
	}
	if (c == 'X')
	{
		tmp = va_arg(*ap, int);
		count += count_hexa_x_x(tmp);
		ft_putnbr_base_x_x(tmp, "0123456789ABCDEF");
	}
	if (c == '%')
	{
		ft_putchar('%');
		count++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	ap;

	va_start(ap, str);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += ft_check_char(str[i + 1], &ap);
			i += 2;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
			count ++;
		}
		if (str[i] == '\0')
			break ;
	}
	va_end(ap);
	return (count);
}
