/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:23:23 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/23 11:36:22 by mede-sou         ###   ########.fr       */
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

char	**make_new_tab_cmd(t_minishell *minishell)
{
	char	**new_tab_cmd;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
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
			new_tab_cmd[j] = 
				ft_strdup(minishell->parse[minishell->index_cmd].tab_cmd[k]);
			if (new_tab_cmd[j] == NULL)
				return (NULL);
			k++;
			j++;
		}
	}
	new_tab_cmd[j] = NULL;
	return (new_tab_cmd);
}


int	ft_fork1(t_minishell *minishell, int *pipefd, int tmp_fd)
{
	pid_t	pid;
	char	*path;
	char	**cmd;

	// cmd = NULL;
	minishell->fd = minishell->parse[minishell->index_cmd].fd_in;
	if (check_builtins_env(minishell->parse[minishell->index_cmd].tab_cmd) == 1)
	{	
		if (minishell->count == 0)
			builtins(minishell);
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
		if (minishell->parse[minishell->index_cmd].file_in != NULL)
		{
			printf("REDIR_R\n");
			cmd = make_new_tab_cmd(minishell);
			printf("cmd[0] = %s\n",cmd[0]);
			printf("cmd[1] = %s\n",cmd[1]);
			if (minishell->parse[minishell->index_cmd].fd_out > 0)
				dup2(minishell->parse[minishell->index_cmd].fd_out, STDOUT);
			if (minishell->parse[minishell->index_cmd].fd_in > 0)
				dup2(minishell->parse[minishell->index_cmd].fd_in, STDIN);
			if ((path = get_path(minishell->environ, cmd)) == NULL)
			{
				printf("%s: command not found\n", cmd[0]);
				exit (1);
			}
			if (execve(path, cmd, minishell->tab_env) == -1)
				fprintf(stderr, "Error: execve failed");
		}
		else if (check_builtins(minishell->parse[minishell->index_cmd].tab_cmd) == 1)
		{
			if (minishell->index_cmd < minishell->count)
				dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
			builtins(minishell);
			exit(1);
		}
		else
		{
			if ((path = get_path(minishell->environ, minishell->parse[minishell->index_cmd].tab_cmd)) == NULL)
			{
				printf("%s: command not found\n", minishell->parse[minishell->index_cmd].tab_cmd[0]);
				exit (1);
			}
			if (minishell->parse[minishell->index_cmd].type != REDIR_R && minishell->index_cmd < minishell->count)
				dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		if (execve(path, minishell->parse[minishell->index_cmd].tab_cmd, minishell->tab_env) == -1)
			fprintf(stderr, "Error: execve failed");
	}
	return (1);
}
