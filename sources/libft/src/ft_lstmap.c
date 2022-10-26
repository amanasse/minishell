/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:43:55 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:32:40 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*save;

	if (!f || !del)
		return (NULL);
	save = NULL;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp == NULL)
		{
			ft_lstclear(&save, del);
			return (NULL);
		}
		ft_lstadd_back(&save, tmp);
		lst = lst->next;
	}
	return (save);
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