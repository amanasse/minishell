/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/04 13:55:51 by amanasse         ###   ########.fr       */
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

	// ft_memset((void*) shell, 0, 0);
	shell.environ = NULL;
	copy_of_env(env, &shell);
	cmd = NULL;
	cmd = malloc(sizeof(char *) * 3);
	if (cmd == NULL)
		return (0);
	memset(cmd, 0, 4);
	cmd[0] = "cd";
	cmd[1] = ".";
	cmd[2] = NULL;
	// cmd[1] = "pwd";





	ft_view_env(shell.environ);
	builtins(cmd, shell.environ);
	ft_lstclear_env(shell.environ);

	
	

	
	// cmd[3] = "-n";
	// cmd[3] = "..";
	// cmd[4] = "ahah";
	// cmd_cd(cmd);
	// cmd_pwd(cmd);
	// cmd_exit(cmd);
	// free(cmd);


	
	return (0);
}