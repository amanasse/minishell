/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:47:35 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/31 09:00:37 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ms	*ft_lstnew_ms(void *content)
{
	t_ms	*element;

	element = malloc(sizeof(t_ms));
	if (element == NULL)
		return (NULL);
	element->next = NULL;
	element->str = content;
	element->type = 0;
	return (element);
}

void	ft_lstadd_back_ms(t_ms **lst, t_ms *new)
{
	t_ms	*tmp;

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

void    ft_view_lst(t_ms *lst)
{
    int    i;

    i = 1;
    while (lst->next != NULL)
    {
        printf("lst[%d] = %s\nSon adresse : %p\nSon type : %d\n", i, lst->str, lst, lst->type);
        lst = lst->next;
        i++;
    }
	printf("lst[%d] = %s\nSon adresse : %p\nSon type : %d\n", i, lst->str, lst, lst->type);
    printf("-----------------\n");
}