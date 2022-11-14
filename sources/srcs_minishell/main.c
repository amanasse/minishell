/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/14 12:11:14 by amanasse         ###   ########.fr       */
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
	cmd = malloc(sizeof(char *) * 5);
	if (cmd == NULL)
		return (0);
	memset(cmd, 0, 4);
	cmd[0] = "export";
	cmd[1] = "lol=AHAHAH";
	cmd[2] = "COUCOU=MDR";
	cmd[3] = "PAGER=LOL";
	cmd[4] = NULL;
	// cmd[4] = "les garsn";
	// cmd[2] = NULL;
	// cmd[1] = "pwd";




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