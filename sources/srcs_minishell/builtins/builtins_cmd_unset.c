/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:17 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/16 16:21:32 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

int	var_disepear(char *str, t_shell *shell, t_unset *unset)
{
	unset->tmp = shell->environ;
	while (shell->environ != NULL)
	{
		if (ft_strnstr(shell->environ->str, str, unset->i) == 0)
		{
			if (shell->environ->str[unset->i] == '=')
			{
				unset->tmp2 = shell->environ;
				free(shell->environ->str);
				unset->tmp_next = shell->environ->next;
				unset->tmp_before->next = unset->tmp_next;
				if (unset->tmp_next)
					unset->tmp_next->next = shell->environ->next->next;
				shell->environ = unset->tmp;
				return (free(unset->tmp2), free(str), 0);
			}
		}
		unset->tmp_before = shell->environ;
		if (shell->environ->next)
			shell->environ = shell->environ->next;
	}
	return (free(str), 0);
}

int	unset_cmd(char *str, t_shell *shell, t_unset *unset)
{
	(void) *shell;
	while (str[unset->i] && str[unset->i] != '=')
		unset->i++;
	while (str && str[unset->count] != '\0')
		unset->count++;
	unset->compare = malloc(sizeof(char) * (unset->i + 2));
	if (unset->compare == NULL)
		return (-1);
	unset->compare = ft_strcpy(unset->compare, str);
	var_disepear(unset->compare, shell, unset);
	return (0);
}

void	init_unset(t_unset *unset)
{
	unset->i = 0;
	unset->var_env = 0;
	unset->is_ok = 0;
	unset->count = 0;
}

int	cmd_unset(char **cmd, t_shell *shell)
{
	t_unset	unset;
	int		i;

	i = 1;
	if (cmd[1])
	{
		init_unset(&unset);
		while (cmd[i])
		{
			unset_cmd(cmd[i], shell, &unset);
			i++;
		}		
	}
	return (0);
}
