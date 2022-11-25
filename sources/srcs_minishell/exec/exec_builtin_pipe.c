/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:16:25 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/25 09:38:37 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_minishell *minishell, int *pipefd)
{
	if (minishell->index_cmd < minishell->count)
		dup2(pipefd[1], 1);
	close_fd(pipefd);
	builtins(minishell);
	exit(1);
}

void	exec_pipe(t_minishell *minishell, int *pipefd)
{
	char	*path;
	
	if ((path = get_path(minishell->environ,
		minishell->parse[minishell->index_cmd].tab_cmd, minishell)) == NULL)
	{
		path = minishell->parse[minishell->index_cmd].tab_cmd[0];
		if (access(path, F_OK) == 0)
			execve(path, minishell->parse[minishell->index_cmd].tab_cmd,
				minishell->tab_env);
		printf("%s: command not found\n",
			minishell->parse[minishell->index_cmd].tab_cmd[0]);
		exit(127);
	}
	if (minishell->index_cmd < minishell->count)
		dup2(pipefd[1], 1);
	close_fd(pipefd);
	minishell->shell.status = execve(path,
		minishell->parse[minishell->index_cmd].tab_cmd,	minishell->tab_env);
}