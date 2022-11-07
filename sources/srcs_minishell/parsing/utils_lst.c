/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:47:35 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/07 11:23:19 by mede-sou         ###   ########.fr       */
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

    i = 0;
    while (lst->next != NULL)
    {
        printf("lst[%d] = [%s]\n", i, lst->str);
        printf("type = %d\n", lst->type);
        lst = lst->next;
        i++;
    }
	printf("lst[%d] = [%s]\n", i, lst->str);
    printf("type = %d\n", lst->type);
    printf("-----------------\n");
}

void	ft_lstclear_ms(t_ms *lst)
{
	t_ms	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

// void	ft_join_maillons(t_ms **lex)
// {
// 	t_ms	*temp;

// 	temp = *lex;
// 	while (temp->next != NULL)
// 	{
// 		if (temp->type == 0)
// 		{
// 			if ((temp->next->type == 1 || temp->next->type == 1) && temp->next != NULL)
// 			{
// 				temp->str = ft_strcat(temp->str, temp->next->str);
// 				temp->next = temp->next->next;
// 				temp->type = 1;
// 				if (temp->next == NULL)
// 					break ;
// 			}
// 			else
// 				temp = temp->next;
// 		}
// 		else if (temp->type == 1)
// 		{
// 			if (temp->next->type == 0 && temp->next != NULL)
// 			{
// 				temp->str = ft_strcat(temp->str, temp->next->str);
// 				temp->next = temp->next->next;
// 				if (temp->next == NULL)
// 					break ;
// 			}
// 			else
// 				temp = temp->next;
// 		}
// 		else
// 			temp = temp->next;
// 	}
// }