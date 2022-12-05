/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_close_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:28:43 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/05 16:29:50 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	dupper_child(int tmp_fd)
{
	if (tmp_fd > 0)
	{
		dup2(tmp_fd, 0);
		close(tmp_fd);
	}
}

void	check_for_close(t_minishell *m, int tmp_pipefd)
{
	if (m->parse[m->index_cmd].fd_out
		!= STDOUT_FILENO && m->parse[m->index_cmd].fd_out != -1)
		close(m->parse[m->index_cmd].fd_out);
	if (m->parse[m->index_cmd].fd_in
		!= STDIN_FILENO && m->parse[m->index_cmd].fd_in != -1)
		close(m->parse[m->index_cmd].fd_in);
	if (tmp_pipefd > 0)
		close(tmp_pipefd);
}
