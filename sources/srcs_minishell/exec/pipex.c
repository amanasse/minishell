/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:23:23 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/06 16:56:40 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (minishell->if_builtins == 0)
			minishell->shell.status = loc / 256;
		i++;
	}
}

int	ft_fork(t_minishell *m, int *pipefd, int tmp_fd)
{
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
		signal_child();
		dupper_child(tmp_fd);
		if (m->parse[m->index_cmd].type == 3
			|| m->parse[m->index_cmd].type == 4
			|| m->parse[m->index_cmd].type == 5
			|| m->parse[m->index_cmd].type == 6)
			exec_redirection(m, pipefd);
		else if (check_builtins(m->parse[m->index_cmd].tab_cmd, m) == 1)
			exec_builtin(m, pipefd);
		else
			exec_pipe(m, pipefd);
	}
	return (1);
}

int	execution(t_minishell *m)
{
	int	tmp_pipefd;
	int	pipefd[2];

	tmp_pipefd = 0;
	m->index_cmd = 0;
	while (m->parse[m->index_cmd].tab_cmd)
	{
		if (pipe(pipefd) == -1)
			return (-1);
		if (m->parse[m->index_cmd].type == HEREDOC)
			tmp_pipefd = 0;
		env_in_tab(m);
		if (m->tab_env == NULL)
			return (-1);
		ft_fork(m, pipefd, tmp_pipefd);
		free(m->tab_env);
		m->tab_env = NULL;
		close(pipefd[1]);
		check_for_close(m, tmp_pipefd);
		tmp_pipefd = pipefd[0];
		m->index_cmd++;
	}
	close_pipe_and_wait(tmp_pipefd, m);
	m->if_heredoc = 0;
	return (0);
}
