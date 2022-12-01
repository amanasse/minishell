/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:40:55 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/25 16:59:01 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	exit_non_numeric(char **cmd)
{
	printf("exit\nminishell: exit: %s: numeric argument required\n", cmd[1]);
	return (2);
}

int	exit_negatif(int i)
{
	int	j;
	int	k;

	k = 0;
	j = 256;
	while (k >= i)
	{
		if (j == 0)
			j = 256;
		j--;
		k--;
	}
	j++;
	printf("exit\n");
	return (j);
}

int	exit_positif(int i)
{
	int	k;
	int	j;

	j = 0;
	k = 0;
	while (k <= i)
	{
		if (j == 256)
			j = 0;
		j++;
		k++;
	}
	j--;
	printf("exit\n");
	return (j);
}

int	cmd_exit(char **cmd)
{
	int	i;

	if (!cmd[1])
		printf("exit\n");
	else
	{
		if (cmd[2])
			return (printf("exit\nminishell: exit: too many arguments\n"), 1);
		else
		{
			if (ft_atoi_check(cmd[1]) == -1)
				return (exit_non_numeric(cmd));
			else
			{
				i = ft_atoi(cmd[1]);
				if (i >= 0)
					return (exit_positif(i));
				if (i < 0)
					return (exit_negatif(i));
			}
		}
	}
	return (0);
}
