/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:16:25 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/28 14:06:20 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_minishell *minishell, int *pipefd)
{
	if (minishell->index_cmd < minishell->count)
		dup2(pipefd[1], 1);
	close_fd(pipefd);
	builtins(minishell);
	exit(minishell->shell.status);
}

void	exec_pipe(t_minishell *m, int *pipefd)
{
	char	*path;

	path = get_path(m->environ, m->parse[m->index_cmd].tab_cmd, m);
	if (path == NULL)
	{
		path = m->parse[m->index_cmd].tab_cmd[0];
		if (access(path, F_OK) == 0)
			execve(path, m->parse[m->index_cmd].tab_cmd,
				m->tab_env);
		printf("%s: command not found\n",
			m->parse[m->index_cmd].tab_cmd[0]);
		m->shell.status = 127;
		exit(m->shell.status);
	}
	if (m->index_cmd < m->count)
		dup2(pipefd[1], 1);
	close_fd(pipefd);
	m->shell.status = execve(path, m->parse[m->index_cmd].tab_cmd, m->tab_env);
}
