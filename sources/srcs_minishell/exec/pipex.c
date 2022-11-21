/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:23:23 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/21 18:07:48 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path(t_env *environ, char **cmd)
{
	char  *path;
	int   i;
	char  *path_slash;
	char  **split_paths;
	
	i = 0;
	while (environ)
	{
		if (ft_strncmp(environ->str, "PATH", 4) == 0)
			break ;
		environ = environ->next;
	}
	split_paths = ft_split(environ->str + 5, ':');
	if (split_paths == NULL)
		return (NULL);
	while (split_paths[i])
	{
		path_slash = ft_strjoin(split_paths[i], "/");
		if (path_slash == NULL)
		{
			i = 0;
			while (split_paths[i])
			{
				free(split_paths[i]);
				i++;
			}
			return (NULL);
		}
		path = ft_strjoin(path_slash, cmd[0]);
		if (path == NULL)
		{
			free(path_slash);
			i = 0;
			while (split_paths[i])
			{
				free(split_paths[i]);
				i++;
			}
			return (NULL);
		}
			
		free(path_slash);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (split_paths[i])
	{
		free(split_paths[i]);
		i++;
	}
	free(split_paths);
	return (NULL);
}

int	ft_fork1(t_minishell *minishell, int *pipefd, int tmp_fd)
{
	pid_t	pid;
	char	*path;

	minishell->fd = minishell->parse[minishell->index_cmd].fd_in;
	if (check_builtins_env(minishell->parse[minishell->index_cmd].tab_cmd) == 1)
	{	
		if (minishell->count == 0)
			builtins(minishell->parse[minishell->index_cmd].tab_cmd, minishell);
		return (minishell->shell.status);
	}
	pid = fork();
	if (pid == 0)
	{
		if (tmp_fd > 0)
		{
			dup2(tmp_fd, 0);
			close(tmp_fd);
		}
		if (check_builtins(minishell->parse[minishell->index_cmd].tab_cmd) == 1)
		{
			if (minishell->index_cmd < minishell->count)
				dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
			builtins(minishell->parse[minishell->index_cmd].tab_cmd, minishell);
			exit(1);
		}
		else
		{
			if ((path = get_path(minishell->environ, minishell->parse[minishell->index_cmd].tab_cmd)) == NULL)
			{
				printf("%s: command not found\n", minishell->parse[minishell->index_cmd].tab_cmd[0]);
				exit (1);
			}
			if (minishell->index_cmd < minishell->count)
				dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
			execve(path, minishell->parse[minishell->index_cmd].tab_cmd, minishell->tab_env);
		}
	}
	return (1);
}
