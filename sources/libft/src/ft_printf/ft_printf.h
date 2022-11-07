/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:26:23 by amanasse          #+#    #+#             */
/*   Updated: 2022/06/07 09:26:40 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <ctype.h>
# include <unistd.h>
# include <limits.h>

unsigned int	count_u(unsigned int nb);
void			ft_putnbr_base_x_x(unsigned int nb, char *base);
void			ft_putnbr_base(unsigned long long nb, char *base);
void			ft_putchar(char c);
int				ft_strlen(char *s);
int				ft_string(char *str);
int				ft_char(int c);
void			ft_putnbr_u(unsigned int n);
int				ft_putnbr_d_i(int n);
int				count_hexa(unsigned long long nb);
int				count_nb(int nb);
int				ft_printf(const char *str, ...);
int				count_hexa_x_x(unsigned int nb);

#endif