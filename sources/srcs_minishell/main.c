/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/02 15:21:38 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int main(int argc, char **argv, char **env)
{
	char **cmd;
	int i;
	(void) argc;
	(void) **argv;
	(void) **env;
	
	cmd = malloc(sizeof(char *) * (2 + 1));
	i = 0;
	cmd[i] = "exit";
	printf("cmd[0] = %s\n", cmd[i]);
	cmd[++i] = "lol";
	printf("cmd[1] = %s\n", cmd[i]);
	cmd_cd(cmd);
	cmd_pwd(cmd);
	cmd_exit(cmd);


	
	return (0);
}