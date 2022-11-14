/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:38:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/14 10:38:41 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void	ft_view_env(t_env *lst)
{
	int i;

	i = 0;
	while (lst->next != NULL)
	{
		if(lst->printable == 1)
			printf("[%d]%s\n",i, lst->str);
		lst = lst->next;
		i++;
	}
	if(lst->printable == 1)
		printf("[%d]%s\n", i, lst->str);
}

void	ft_lstclear_env(t_env *lst)
{
	t_env	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->str);
		free(tmp);
	}
}

t_env	*ft_lstnew_env(void *content)
{
	t_env	*element;
	int i;

	i = ft_strlen(content);
	element = malloc(sizeof(t_env));
	if (element == NULL)
		return (NULL);
	element->next = NULL;
	element->str = (char*)malloc(sizeof(char) * i + 1);
	if (element->str == NULL)
		return (NULL);
	element->str = ft_strcpy(element->str, content);
	i = 0;
	while (element->str[i])
	{
		if (element->str[i] == '=')
		{
			element->printable = 1;
			break ;
		}			
		i++;
		element->printable = 0;
	}
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
