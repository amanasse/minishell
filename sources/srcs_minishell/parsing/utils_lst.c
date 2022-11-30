/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:47:35 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/30 16:27:00 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lstms	*ft_lstnew_ms(void *content, int type)
{
	t_lstms	*element;

	element = malloc(sizeof(t_lstms));
	if (element == NULL)
		return (NULL);
	element->next = NULL;
	element->str = content;
	element->type = type;
	return (element);
}

void	ft_lstadd_back_ms(t_lstms **lst, t_lstms *new)
{
	t_lstms	*tmp;

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

void	ft_lstadd_front_ms(t_lstms **lst, t_lstms *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_view_lst(t_lstms *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		printf("lex[%d] = [%s]\n", i, lst->str);
		printf("type = %d\n", lst->type);
		lst = lst->next;
		i++;
	}
	printf("lex[%d] = [%p]\n", i, lst);
	printf("-----------------\n");
}

void	ft_lstclear_ms(t_lstms *lst)
{
	t_lstms	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

int	ft_lstsize_ms(t_lstms *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
