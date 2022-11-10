/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:38 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/10 11:26:04 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void	cmd_echo(char **cmd)
{
	int	i;
	int	j;
	int	ok;
	int	count_cmd;

	i = 0;
	j = 1;
	ok = 1;
	count_cmd = 0;
	if (cmd[1] != NULL)
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
				while (cmd[i][j] == 'n' && cmd[i][j] != '\0')
					j++;
				if (cmd[i][j - 1] == 'n' && cmd[i][j] == '\0')
					ok = 0;
				j = i;
				if (ok == 0)
					i++;
			}
			if (count_cmd > 1)
			{
				while (i < count_cmd)
				{
					if (ok == 0 && (ft_strnstr(cmd[i], "-n", 2)) == 0)
					{	
						printf("cmd[%d] = [%s]\n", i, cmd[i]);
						j = 1;
						while (cmd[i][j] == 'n' && cmd[i][j] != '\0')
							j++;
						if (cmd[i][j - 1] == 'n' && cmd[i][j] != '\0')
							break ;
						i++;
					}
					else
						break ;
				}
				printf("i = %d\n", i);
				while (i < count_cmd)
				{
					printf ("%s", cmd[i]);
					if (i + 1 != count_cmd)
						printf (" ");
					i++;
				}
			}
			if (ok == 1)
				printf ("\n");
		}
	}
	else
		printf ("\n");
}
