/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/15 14:57:32 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char **cmd;
	(void) argc;
	(void) **argv;
	(void) **env;

	shell.environ = NULL;
	copy_of_env(env, &shell);
	cmd = NULL;
	cmd = malloc(sizeof(char *) * 8);
	if (cmd == NULL)
		return (0);
	memset(cmd, 0, 4);
	cmd[0] = "export";
	cmd[1] = "SHELL=smw";
	cmd[2] = "-5654";
	cmd[3] = "LOL=DKWOKDW";
	cmd[4] = "hdh=DKWOKDW";
	cmd[5] = "dpwld=";
	cmd[6] = "dqmdqmd";
	cmd[7] = NULL;




	builtins(cmd, &shell);
	ft_view_env(shell.environ);
	ft_lstclear_env(shell.environ);
	
	
	// free(shell.old_pwd);
	// free(shell.pwd);
	free(cmd);
	
	

	
	// cmd[3] = "-n";
	// cmd[3] = "..";
	// cmd[4] = "ahah";
	// cmd_cd(cmd);
	// cmd_pwd(cmd);
	// cmd_exit(cmd);
	// free(cmd);


	
	return (0);
}