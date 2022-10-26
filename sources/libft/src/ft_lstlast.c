/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:01:41 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:32:36 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	return (tmp);
}
/*
int main() 
{

    t_list    *tete;
    t_list     manass;
    memset(&manass, 0, sizeof(t_list));
    t_list     marvin;
    memset(&marvin, 0, sizeof(t_list));
    t_list     tim;
    memset(&tim, 0, sizeof(t_list));

    tete = &manass;
    manass.next = &tim;
    tim.next = &marvin;
    marvin.next = NULL;

    printf("---------------------------------------------\n");
    printf("adresse de manass = %p\n", &manass);
    printf("next de manass = %p\n", manass.next);
    printf("adresse de tim = %p\n", &tim);
    printf("next de tim = %p\n", tim.next);
    printf("adresse de marvin = %p\n", &marvin);
    printf("next de marvin = %p\n", marvin.next);
    printf("---------------------------------------------\n");
    printf("---------------------------------------------\n");

    printf("last marvin = %p\n", ft_lstlast(tete));
    printf("nouvelle adresse de tete = %p\n", tete);
}
*/