/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:23:23 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/21 13:29:03 by amanasse         ###   ########.fr       */
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

int	ft_fork1(t_minishell *minishell, int *pipefd, int tmp_fd, char **cmd)
{
	pid_t	pid;
	char	*path;
	char	**env;
	
	pid = fork();
	env = env_in_tab(minishell);
	
	if (pid == 0)
	{
		if (tmp_fd > 0)
		{
			dup2(tmp_fd, 0);
			close(tmp_fd);
		}
		if (check_builtins(cmd) == 1)
		{
			printf("DEBUG\n");
			if(minishell->index_cmd < minishell->count)
				dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
			builtins(cmd, minishell);
			exit(1);
		}
		else
		{
			if ((path = get_path(minishell->environ, cmd)) == NULL)
			{
				printf("%s: command not found\n", cmd[0]);
				exit (1);
			}
			printf("minishell->index_cmd = %d", minishell->index_cmd);
			printf("minishell->count - 1 = %d", minishell->count);
			if(minishell->index_cmd < minishell->count)
			{
				printf("cmd %s\n", cmd[0]);
				dup2(pipefd[1], 1);
			}
			close(pipefd[0]);
			close(pipefd[1]);
			execve(path, cmd, env);
		}
	}
	return (1);
}
