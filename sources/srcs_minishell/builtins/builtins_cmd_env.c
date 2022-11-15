/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:03:50 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/15 16:48:23 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

int	cmd_env(char **cmd, t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->environ;
	if (cmd[1] == NULL)
		ft_view_env(tmp);
	else
	{
		printf("env: '%s': No such file or directory\n", cmd[1]);
		return (127);
	}
	return (0);
}
