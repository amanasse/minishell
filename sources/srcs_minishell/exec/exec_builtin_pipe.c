/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:16:25 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/23 13:33:42 by mede-sou         ###   ########.fr       */
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
		minishell->parse[minishell->index_cmd].tab_cmd)) == NULL)
	{
		printf("%s: command not found\n",
			minishell->parse[minishell->index_cmd].tab_cmd[0]);
		exit (1);
	}
	if (minishell->index_cmd < minishell->count)
		dup2(pipefd[1], 1);
	close_fd(pipefd);
	if (execve(path, minishell->parse[minishell->index_cmd].tab_cmd,
		minishell->tab_env) == -1)
		fprintf(stderr, "Error: execve failed");
}