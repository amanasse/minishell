/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:17 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/28 11:23:34 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	var_disappear2(t_minishell *minishell, t_unset *unset)
{
	if (minishell->environ->str[unset->i] == '=')
	{
		if (!unset->tmp_before)
		{	
			free(minishell->environ->str);
			minishell->environ->str = NULL;
			minishell->environ = unset->tmp->next;
			unset->tmp = NULL;
			free(unset->tmp);
			return (1);
		}
		unset->tmp2 = minishell->environ;
		free(minishell->environ->str);
		unset->tmp_next = minishell->environ->next;
		unset->tmp_before->next = unset->tmp_next;
		if (unset->tmp_next)
			unset->tmp_next->next = minishell->environ->next->next;
		minishell->environ = unset->tmp;
		return (free(unset->tmp2), 0);
	}
	return (0);
}

int	var_disappear(char *str, t_minishell *minishell, t_unset *unset)
{
	int	bool;

	bool = 0;
	unset->tmp = minishell->environ;
	unset->tmp_before = NULL;
	while (minishell->environ != NULL)
	{
		if (ft_strnstr(minishell->environ->str, str, unset->i) == 0)
		{
			if (var_disappear2(minishell, unset) == 1)
			{
				bool = 1;
				break ;
			}
		}
		unset->tmp_before = minishell->environ;
		minishell->environ = minishell->environ->next;
	}
	if (bool != 1)
		minishell->environ = unset->tmp;
	return (free(str), 0);
}

int	unset_cmd(char *str, t_minishell *minishell, t_unset *unset)
{
	while (str[unset->i] && str[unset->i] != '=')
		unset->i++;
	while (str && str[unset->count] != '\0')
		unset->count++;
	unset->compare = malloc(sizeof(char) * (unset->i + 2));
	if (unset->compare == NULL)
		return (-1);
	unset->compare = ft_strcpy(unset->compare, str);
	var_disappear(unset->compare, minishell, unset);
	return (0);
}

void	init_unset(t_unset *unset)
{
	unset->i = 0;
	unset->var_env = 0;
	unset->is_ok = 0;
	unset->count = 0;
}

int	cmd_unset(char **cmd, t_minishell *minishell)
{
	t_unset	unset;
	int		i;

	i = 1;
	if (cmd[1])
	{
		init_unset(&unset);
		while (cmd[i])
		{
			unset_cmd(cmd[i], minishell, &unset);
			i++;
		}		
	}
	return (0);
}
