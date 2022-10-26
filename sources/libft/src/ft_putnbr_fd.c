/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:00:23 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:33:17 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	ok;

	ok = 0;
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	if (n == -2147483648)
	{
		ok = 1;
		write(fd, "2147483648", 10);
	}
	else if (n < 10)
	{
		ft_putchar_fd(n + 48, fd);
		ok = 1;
	}
	else
		ft_putnbr_fd(n / 10, fd);
	if (ok == 0)
		ft_putchar_fd((n % 10) + 48, fd);
}
/*
int main()
{
ft_putnbr_fd(-2147483648, 1);
return (0);
}
*/