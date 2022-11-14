/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:40:55 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/14 15:03:01 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

// PENSER A DETRUIRE LE TABLEAU DE CMD + ENV avant chaque RETURN --> destroy_cmd(cmd, env);
int	cmd_exit(char **cmd)
{
	int	i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if (!cmd[1])
	{
		printf("exit\n");
		return (0);
	}
	else
	{
		if (cmd[2])
		{
			printf("exit\nbash: exit: too many arguments\n");
			return (1);
		}
		else
		{
			if (ft_atoi_check(cmd[1]) == -1)
			{
				printf("exit\nbash: exit: %s: numeric argument required\n", cmd[1]);
				return (2);
			}
			else
			{
				i = ft_atoi(cmd[1]);
				if (i > 0 && i <= 255)
				{
					printf("exit %d\n", i);
					return (i);
				}
				if (i > 255 && i > 0)
				{
					while (k <= i)
					{
						if (j == 256)
							j = 0;
						j++;
						k++;
					}
					j--;
					printf("exit %d\n", j);
					return (j);
				}
				if (i < 0)
				{
					j = 256;
					while (k >= i)
					{
						if (j == 0)
							j = 256;
						j--;
						k--;
					}
					j++;
					printf("exit %d\n", j);			
					return (j);
				}
			}
		}
	}
	return (0);
}
