/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:16:25 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/23 12:23:01 by mede-sou         ###   ########.fr       */
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

