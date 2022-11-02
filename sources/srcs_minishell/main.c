/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/02 17:43:54 by amanasse         ###   ########.fr       */
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
	
	// cmd = NULL;
	cmd = malloc(sizeof(char *) * 5);
	if (cmd == NULL)
		return (0);
	// memset(cmd, 0, 4);
	cmd[0] = "echo";
	// cmd[1] = "-n";
	// cmd[1] = "-n";
	cmd[1] = "lola";
	cmd[2] = "ahah";
	cmd[3] = NULL;
	// cmd_cd(cmd);
	// cmd_pwd(cmd);
	// cmd_exit(cmd);
	cmd_echo(cmd);
	free(cmd);


	
	return (0);
}