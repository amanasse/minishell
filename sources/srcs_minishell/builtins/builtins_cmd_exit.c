/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:40:55 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/10 11:21:21 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

int	cmd_exit(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[1])
	{
		printf("exit\n");
		/*destroy_cmd(cmd);*/
		return (0);
	}
	else
	{
		if (cmd[2])
		{
			printf("exit\nbash: exit: too many arguments\n");
			// destroy_cmd(cmd);
			return (0);
		}
		else
		{
			if (ft_atoi_check(cmd[1]) == -1)
			{
				printf("exit\nbash: exit: %s: numeric argument required\n", cmd[1]);
				// destroy_cmd(cmd);
				return (0);
			}
			else
			{
				i = ft_atoi(cmd[1]);
				printf("exit %d\n", i);
				// destroy_cmd(cmd);
				return (i);
			}
		}
	}
}
