/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:17 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/16 17:41:56 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void	pop(t_env **environ)
{
	t_env	*first;
	t_env	*tmp;

	first = *environ;
	tmp = first;
	*environ = first->next;
	free(first);
}

int	var_disepear(char *str, t_env *environ, t_unset *unset)
{
	unset->tmp = environ;
	unset->tmp_before = NULL;
	while (environ != NULL)
	{
		if (ft_strnstr(environ->str, str, unset->i) == 0)
		{
			if (environ->str[unset->i] == '=')
			{
				if (!unset->tmp_before)
					return (pop(&environ), 0);
				unset->tmp2 = environ;
				free(environ->str);
				unset->tmp_next = environ->next;
				unset->tmp_before->next = unset->tmp_next;
				if (unset->tmp_next)
					unset->tmp_next->next = environ->next->next;
				environ = unset->tmp;
				return (free(unset->tmp2), free(str), 0);
			}
		}
		unset->tmp_before = environ;
		if (environ->next)
			environ = environ->next;
	}
	return (free(str), 0);
}

int	unset_cmd(char *str, t_env *environ, t_unset *unset)
{
	while (str[unset->i] && str[unset->i] != '=')
		unset->i++;
	while (str && str[unset->count] != '\0')
		unset->count++;
	unset->compare = malloc(sizeof(char) * (unset->i + 2));
	if (unset->compare == NULL)
		return (-1);
	unset->compare = ft_strcpy(unset->compare, str);
	var_disepear(unset->compare, environ, unset);
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
			unset_cmd(cmd[i], minishell->environ, &unset);
			i++;
		}		
	}
	return (0);
}