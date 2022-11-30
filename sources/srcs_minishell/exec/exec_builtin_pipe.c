/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:16:25 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/30 15:39:49 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_minishell *minishell, int *pipefd)
{
	if (minishell->index_cmd < minishell->count)
		dup2(pipefd[1], STDOUT_FILENO);
	close_fd(pipefd);
	builtins(minishell);
	exit(minishell->shell.status);
}

void	exec_pipe(t_minishell *m, int *pipefd)
{
	char	*path;
	int i;

	i = 0;

	path = get_path(m->environ, m->parse[m->index_cmd].tab_cmd, m);
	// printf("cmd = %s\n",  m->parse[m->index_cmd].tab_cmd[0]);
	// printf("index = %d\n", m->index_cmd);
	// printf("count = %d\n", m->count);
	// printf("fd in = %d\n", m->parse[m->index_cmd].fd_in);
	// printf("fd out = %d\n", m->parse[m->index_cmd].fd_out);
	// printf("std fd in = %d\n", STDIN_FILENO);
	// printf("std fd out = %d\n", STDOUT_FILENO);
	if (path == NULL)
	{
		path = m->parse[m->index_cmd].tab_cmd[0];
		if (access(path, F_OK) == 0)
			execve(path, m->parse[m->index_cmd].tab_cmd,
				m->tab_env);
		while (path[i])
		{
			if (path[i] == '/')
			{
				printf("%s: not a directory\n", m->parse[m->index_cmd].tab_cmd[0]);
				m->shell.status = 126;
				exit(m->shell.status);
			}
			i++;
		}
		printf("%s: command not found\n", m->parse[m->index_cmd].tab_cmd[0]);
		m->shell.status = 127;
		exit(m->shell.status);
	}
	if (m->index_cmd < m->count)
		dup2(pipefd[1], STDOUT_FILENO);
	close_fd(pipefd);
	m->shell.status = execve(path, m->parse[m->index_cmd].tab_cmd, m->tab_env);
}
