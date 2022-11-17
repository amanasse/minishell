/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:03:50 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/17 11:58:59 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

int	cmd_env(char **cmd, t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->environ;
	printf("tmp = %p\n", tmp);
	if (cmd[1] == NULL)
		ft_view_env(tmp);
	else
	{
		printf("env: '%s': No such file or directory\n", cmd[1]);
		return (127);
	}
	return (0);
}
