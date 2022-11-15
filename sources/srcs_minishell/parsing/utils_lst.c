/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:47:35 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/15 11:18:40 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_ms	*ft_lstnew_ms(void *content, int type)
{
	t_ms	*element;

	element = malloc(sizeof(t_ms));
	if (element == NULL)
		return (NULL);
	element->next = NULL;
	element->str = content;
	element->type = type;
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
	t_ms	*tmp;
	
	tmp = lst;
	i = 0;
    while (tmp != NULL)
    {
        printf("lex[%d] = [%s]\n", i, tmp->str);
        printf("type = %d\n", tmp->type);
        tmp = tmp->next;
        i++;
    }
	printf("lex[%d] = [%p]\n", i, tmp);
    printf("-----------------\n");
	
}

void	ft_lstclear_ms(t_ms *lst)
{
	t_ms	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	free (lst);
}

int	ft_lstsize_ms(t_ms *lst)
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
