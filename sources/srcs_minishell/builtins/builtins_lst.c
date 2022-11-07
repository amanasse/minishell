/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:38:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/07 14:34:34 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void    ft_view_env(t_env *lst)
{
    int    i;

    i = 0;
    while (lst->next != NULL)
    {
        printf("lst[%d] = %s\n", i, lst->str);
        lst = lst->next;
        i++;
    }
	printf("lst[%d] = %s\n", i, lst->str);
    printf("-----------------\n");
}

void	ft_lstclear_env(t_env *lst)
{
	t_env	*tmp;

	while (lst != NULL)
	{
		if(ft_strnstr(lst->str, "PWD=", 4) == 0)
		{
			free(lst->str);	
		}
		if(ft_strnstr(lst->str, "OLDPWD=", 7) == 0)
		{
			free(lst->str);	
		}
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

t_env	*ft_lstnew_env(void *content)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (element == NULL)
		return (NULL);
	element->next = NULL;
	element->str = content;
	return (element);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

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