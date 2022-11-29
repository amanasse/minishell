/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:05:50 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/29 11:52:18 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_new_tab_cmd(t_minishell *minishell, int i, int j)
{
	char	**new_tab_cmd;
	int		k;

	k = 0;
	while (minishell->parse[minishell->index_cmd].tab_cmd[i])
		i++;
	new_tab_cmd = malloc(sizeof(char *) * i + 1);
	if (new_tab_cmd == NULL)
		return (NULL);
	while (k < i && j < i)
	{
		if (minishell->parse[minishell->index_cmd].tab_cmd[k][0] == '\0')
			k++;
		else
		{
			new_tab_cmd[j]
				= ft_strdup(minishell->parse[minishell->index_cmd].tab_cmd[k]);
			if (new_tab_cmd[j] == NULL)
				return (NULL);
			k++;
			j++;
		}
	}
	new_tab_cmd[j] = NULL;
	return (new_tab_cmd);
}

void	exec_redir_right(t_minishell *minishell)
{
	if (minishell->parse[minishell->index_cmd].fd_out > 0)
		dup2(minishell->parse[minishell->index_cmd].fd_out, STDOUT);
	if (minishell->parse[minishell->index_cmd].fd_in > 0)
		dup2(0, STDIN);
}

void	exec_redir_left(t_minishell *minishell, int *pipefd)
{
	printf("minishell->count = %d\n", minishell->count);
	printf("cmd = %s\n", minishell->parse[minishell->index_cmd].tab_cmd[0]);
	printf("fd out = %d\n", minishell->parse[minishell->index_cmd].fd_out);
	printf("fd in = %d\n", minishell->parse[minishell->index_cmd].fd_in);
	if (minishell->index_cmd < minishell->count)
		dup2(pipefd[1], STDOUT);
	else
	{
		if (minishell->parse[minishell->index_cmd].fd_out > 0)
			dup2(minishell->parse[minishell->index_cmd].fd_out, STDOUT);
		if (minishell->parse[minishell->index_cmd].fd_in > 0)
			dup2(minishell->parse[minishell->index_cmd].fd_in, STDIN);
	}
}

void	exec_heredoc(t_minishell *minishell, int *pipefd)
{
	// (void)pipefd;
	if (minishell->index_cmd < minishell->count)
		dup2(pipefd[1], STDOUT);
	if (minishell->parse[minishell->index_cmd].fd_out > 0)
		dup2(minishell->parse[minishell->index_cmd].fd_out, STDOUT);
	if (minishell->parse[minishell->index_cmd].fd_in > 0)
		dup2(minishell->parse[minishell->index_cmd].fd_in, STDIN);
	printf("minishell->count = %d\n", minishell->count);
	printf("cmd = %s\n", minishell->parse[minishell->index_cmd].tab_cmd[0]);
	printf("fd out = %d\n", minishell->parse[minishell->index_cmd].fd_out);
	printf("fd in = %d\n", minishell->parse[minishell->index_cmd].fd_in);
}

void	exec_redirection(t_minishell *minishell, int *pipefd)
{
	char	**cmd;
	char	*path;

	cmd = make_new_tab_cmd(minishell, 0, 0);
	if (minishell->parse[minishell->index_cmd].delim != NULL)
		cmd = new_cmd_heredoc(minishell, cmd);
	if (minishell->parse[minishell->index_cmd].fd_out == -1
		|| minishell->parse[minishell->index_cmd].fd_in == -1)
	{
		printf("minishell: %s: No such file or directory\n",
			minishell->parse[minishell->index_cmd].file_in);
		exit(1);
	}
	path = get_path(minishell->environ, cmd, minishell);
	if (path == NULL)
	{
		printf("%s: command not found\n", cmd[0]);
		exit(1);
	}
	if (minishell->parse[minishell->index_cmd].type == REDIR_R)
		exec_redir_right(minishell);
	else if (minishell->parse[minishell->index_cmd].type == HEREDOC)
		exec_heredoc(minishell, pipefd);
	else if (minishell->parse[minishell->index_cmd].type == REDIR_L)
		exec_redir_left(minishell, pipefd);
	minishell->shell.status = execve(path, cmd, minishell->tab_env);
}
