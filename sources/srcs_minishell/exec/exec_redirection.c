/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:05:50 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/07 14:09:31 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_new_tab_cmd(t_minishell *ms, int i, int j)
{
	char	**new_tab_cmd;
	int		k;

	k = 0;
	while (ms->parse[ms->index_cmd].tab_cmd[i])
		i++;
	new_tab_cmd = malloc(sizeof(char *) * i + 1);
	if (new_tab_cmd == NULL)
		return (NULL);
	while (k < i && j < i)
	{
		if (ms->parse[ms->index_cmd].tab_cmd[k][0] == '\0')
			k++;
		else
		{
			new_tab_cmd[j] = ft_strdup(ms->parse[ms->index_cmd].tab_cmd[k]);
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
	if (minishell->parse[minishell->index_cmd].fd_out >= 0)
		dup2(minishell->parse[minishell->index_cmd].fd_out, STDOUT_FILENO);
	if (minishell->parse[minishell->index_cmd].fd_in >= 0)
		dup2(minishell->parse[minishell->index_cmd].fd_in, STDIN_FILENO);
}

void	exec_redir_left(t_minishell *minishell, int *pipefd)
{
	if (minishell->index_cmd < minishell->count)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		if (minishell->parse[minishell->index_cmd].fd_in >= 0)
			dup2(minishell->parse[minishell->index_cmd].fd_in, STDIN_FILENO);
	}
	else
	{
		if (minishell->parse[minishell->index_cmd].fd_out >= 0)
			dup2(minishell->parse[minishell->index_cmd].fd_out, STDOUT_FILENO);
		if (minishell->parse[minishell->index_cmd].fd_in >= 0)
			dup2(minishell->parse[minishell->index_cmd].fd_in, STDIN_FILENO);
	}
}

void	exec_cmd(t_minishell *mini, char **cmd, int *pipefd)
{
	char	*path;

	path = get_path(mini->environ, cmd, mini);
	if (path == NULL)
	{
		printf("%s: command not found\n", cmd[0]);
		exit(1);
	}
	if (mini->parse[mini->index_cmd].type == REDIR_R
		|| mini->parse[mini->index_cmd].type == APPEND)
		exec_redir_right(mini);
	else if (mini->if_heredoc == 1)
		exec_heredoc(mini, pipefd);
	else if (mini->parse[mini->index_cmd].type == REDIR_L)
		exec_redir_left(mini, pipefd);
	mini->shell.status = execve(path, cmd, mini->tab_env);
}

void	exec_redirection(t_minishell *mini, int *pipefd)
{
	char	**cmd;

	cmd = make_new_tab_cmd(mini, 0, 0);
	if (mini->parse[mini->index_cmd].delim != NULL && cmd[0] == NULL)
	{
		exec_heredoc(mini, pipefd);
		exit(0);
	}
	if (mini->parse[mini->index_cmd].fd_out == -1
		|| mini->parse[mini->index_cmd].fd_in == -1)
	{
		printf("minishell: %s: No such file or directory\n",
			mini->parse[mini->index_cmd].file_in);
		exit(1);
	}
	if (cmd[0])
		exec_cmd(mini, cmd, pipefd);
	else
	{
		if (cmd)
			free(cmd);
	}
}
