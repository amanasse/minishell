/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:38 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/07 15:14:53 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	init_echo(t_echo *echo)
{
	echo->i = 0;
	echo->j = 1;
	echo->ok = 1;
	echo->count_cmd = 0;
}

void	count_cmd(t_echo *echo, char **cmd)
{
	while (cmd[echo->i] != NULL)
	{
		echo->i++;
		echo->count_cmd++;
	}
	echo->i = 0;
}

void	parse_cmd_n(t_echo *e, char **cmd)
{
	while (cmd[e->i][e->j] == 'n' && cmd[e->i][e->j] != '\0')
		e->j++;
	if (cmd[e->i][e->j - 1] == 'n' && cmd[e->i][e->j] == '\0')
		e->ok = 0;
	e->j = e->i;
	if (e->ok == 0)
		e->i++;
}

int	cmd_echo2(t_echo *e, char **cmd)
{
	while (e->i < e->count_cmd)
	{
		if (e->ok == 0 && (ft_strnstr(cmd[e->i], "-n", 2)) == 0)
		{	
			e->j = 1;
			while (cmd[e->i][e->j] == 'n' && cmd[e->i][e->j] != '\0')
				e->j++;
			if (cmd[e->i][e->j - 1] == 'n' && cmd[e->i][e->j] != '\0')
				break ;
			e->i++;
		}
		else
			break ;
	}
	while (e->i < e->count_cmd)
	{
		printf ("%s", cmd[e->i]);
		if (e->i + 1 != e->count_cmd && cmd[e->i][0] != '\0')
			printf (" ");
		e->i++;
	}
	return (0);
}

int	cmd_echo(char **cmd)
{
	t_echo	echo;

	init_echo(&echo);
	if (cmd[1] != NULL)
	{
		count_cmd(&echo, cmd);
		if (echo.count_cmd > 0)
		{
			echo.i++;
			if (ft_strnstr(cmd[echo.i], "-n", 2) == 0)
				parse_cmd_n(&echo, cmd);
			if (echo.count_cmd > 1)
				cmd_echo2(&echo, cmd);
			if (echo.ok == 1)
				printf ("\n");
		}
	}
	else
		printf ("\n");
	return (0);
}
