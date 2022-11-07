/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:54:18 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:32:16 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (new == NULL)
		return ;
	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}
/*
int main() {

	t_list* ptr_lst;
	t_list*	 tete;
	t_list	 manass;
	memset(&manass, 0, sizeof(t_list));
	t_list	 marvin;
	memset(&marvin, 0, sizeof(t_list));
	t_list	 tim;
	memset(&tim, 0, sizeof(t_list));

	printf("---------------------------------------------\n");
	printf("adresse de manass = %p\n", &manass);
	printf("next de manass = %p\n", manass.next);
	printf("adresse de marvin = %p\n", &marvin);
	printf("next de marvin = %p\n", marvin.next);
	printf("adresse de tim = %p\n", &tim);
	printf("next de tim = %p\n", tim.next);
	printf("---------------------------------------------\n");
	printf("---------------------------------------------\n");

	tete = NULL;
	ptr_lst = &marvin;
	ft_lstadd_back(&tete, ptr_lst);
	ft_lstadd_back(&tete, &tim);

	printf("adresse de manass = %p\n", &manass);
	printf("next de manass = %p\n", manass.next);
	printf("adresse de marvin = %p\n", &marvin);
	printf("next de marvin = %p\n", marvin.next);
	printf("adresse de tim = %p\n", &tim);
	printf("next de tim = %p\n", tim.next);
	printf("---------------------------------------------\n");

	printf("adresse de tete = %p\n", tete);

}
*/