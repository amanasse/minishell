/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/02 13:03:34 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int main(int argc, char **argv, char **env)
{
	char **cmd;
	(void) argc;
	(void) **argv;
	(void) **env;
	
	cmd = malloc(sizeof(char *) * (2 + 1));
	
	cmd[0] = "cd";
	cmd[1] = "..";
	printf("cmd[0] = %s\n", cmd[0]);
	printf("cmd[1] = %s\n", cmd[1]);
	change_directory(cmd);



	
	return (0);
}