/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:23:23 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/29 17:24:41 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	close_pipe_and_wait(int tmp_pipefd, t_minishell *minishell)
{
	int	loc;
	int	i;

	loc = 0;
	if (tmp_pipefd > 0)
		close(tmp_pipefd);
	i = 0;
	while (i < minishell->count + 1)
	{	
		wait(&loc);
			minishell->shell.status = loc / 256;
		i++;
	}
}

int	ft_fork(t_minishell *m, int *pipefd, int tmp_fd)
{
	m->fd = m->parse[m->index_cmd].fd_in;
	if (check_builtins_env(m->parse[m->index_cmd].tab_cmd, m) == 1)
	{
		if (m->count == 0)
			builtins(m);
		return (m->shell.status);
	}
	m->pid = fork();
	if (m->pid == 0)
	{
		m->pid = 1;
		if (tmp_fd > 0)
		{
			dup2(tmp_fd, 0);
			close(tmp_fd);
		}
		if (m->parse[m->index_cmd].file_in != NULL
			|| m->parse[m->index_cmd].delim != NULL)
			exec_redirection(m, pipefd);
		else if (check_builtins(m->parse[m->index_cmd].tab_cmd) == 1)
			exec_builtin(m, pipefd);
		else
			exec_pipe(m, pipefd);
	}
	return (1);
}

int	execution(t_minishell *minishell)
{
	int	tmp_pipefd;
	int	pipefd[2];

	tmp_pipefd = 0;
	minishell->index_cmd = 0;
	while (minishell->parse[minishell->index_cmd].tab_cmd)
	{
		if (pipe(pipefd) == -1)
			return (-1);
		env_in_tab(minishell);
		if (minishell->tab_env == NULL)
			return (-1);
		ft_fork(minishell, pipefd, tmp_pipefd);
		free(minishell->tab_env);
		minishell->tab_env = NULL;
		close(pipefd[1]);
		if (tmp_pipefd > 0)
			close(tmp_pipefd);
		tmp_pipefd = pipefd[0];
		minishell->index_cmd++;
	}
	close_pipe_and_wait(tmp_pipefd, minishell);
	return (0);
}
