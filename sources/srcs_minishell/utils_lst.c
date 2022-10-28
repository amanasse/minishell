/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:47:35 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/28 15:23:43 by mede-sou         ###   ########.fr       */
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