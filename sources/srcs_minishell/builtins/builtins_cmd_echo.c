/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:38 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/08 12:30:13 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void cmd_echo(char **cmd)
{
	int	i;
	int j;
	int k;
	int	count_cmd;

	i = 0;
	j = 0;
	k = 0;
	count_cmd = 0;
	if(cmd[1] != NULL)
	{
		while (cmd[i] != NULL)
		{
			i++;
			count_cmd++;
		}
		i = 0;
		if (count_cmd > 0)
		{
			i++;
			if (ft_strnstr(cmd[i], "-n", 2) == 0)
			{
				k = 1;
				while (cmd[i][j] == 'n' && cmd[i][j] != '\0')
					k++;
				j = i;
				i++;
			}
			if (count_cmd > 1)
			{
				while (i < count_cmd)
				{
					printf ("%s", cmd[i]);
					if (i + 1 != count_cmd)
						printf (" ");
					i++;
				}
			}
		}
		if (cmd[1][k] != '\0' && cmd[1][k - 1] != 'n')
			return ;
		else ((ft_strcmp(cmd[j], "-n")) != 0 || 
			printf ("\n");
	}
	else
		printf ("\n");
}