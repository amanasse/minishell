/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:23:23 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/24 17:30:42 by mede-sou         ###   ########.fr       */
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
	if (environ == NULL)
		return (NULL);
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
		path = NULL;
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

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	ft_fork(t_minishell *minishell, int *pipefd, int tmp_fd)
{
	minishell->fd = minishell->parse[minishell->index_cmd].fd_in;
	if (check_builtins_env(minishell->parse[minishell->index_cmd].tab_cmd) == 1)
	{	
		if (minishell->count == 0)
			builtins(minishell);
		return (minishell->shell.status);
	}
	minishell->pid = fork();
	if (minishell->pid == 0)
	{
		minishell->pid = 1;
		if (tmp_fd > 0)
		{
			dup2(tmp_fd, 0);
			close(tmp_fd);
		}
		if (minishell->parse[minishell->index_cmd].file_in != NULL
			|| minishell->parse[minishell->index_cmd].delimiter != NULL)
			exec_redirection(minishell);
		else if (check_builtins(minishell->parse[minishell->index_cmd].tab_cmd) == 1)
			exec_builtin(minishell, pipefd);
		else
			exec_pipe(minishell, pipefd);
	}
	if (minishell->shell.status == -1)
		fprintf(stderr, "Error: execve failed");
	return (1);
}

int	execution(t_minishell *minishell)
{
	int	tmp_pipefd;
	int	pipefd[2];
	int	i;

	tmp_pipefd = 0;
	minishell->index_cmd = 0;
	// printf("heredoc = %d\n", minishell->parse[0].if_heredoc);
	// if (minishell->parse[0].if_heredoc == 1)
	// {
	// 	if (pipe(pipefd) == -1)
	// 		return (0);
	// 	env_in_tab(minishell);
	// 	if (minishell->tab_env == NULL)
	// 		return (0);
	// 	ft_fork(minishell, pipefd, tmp_pipefd);
	// 	free(minishell->tab_env);
	// 	minishell->tab_env = NULL;
	// 	close(pipefd[1]);
	// 	if (tmp_pipefd > 0)
	// 		close (tmp_pipefd);
	// 	tmp_pipefd = pipefd[0];
	// }
	while (minishell->parse[minishell->index_cmd].tab_cmd)
	{
		if (pipe(pipefd) == -1)
			return (0);
		env_in_tab(minishell);
		if (minishell->tab_env == NULL)
			return (0);
		ft_fork(minishell, pipefd, tmp_pipefd);
		free(minishell->tab_env);
		minishell->tab_env = NULL;
		close(pipefd[1]);
		if (tmp_pipefd > 0)
			close (tmp_pipefd);
		tmp_pipefd = pipefd[0];
		minishell->index_cmd++;
	}
	if (tmp_pipefd > 0)
		close (tmp_pipefd);
	i = 0;
	while (i < minishell->count + 1)
	{	
		wait(NULL);
		i++;
	}
	return (1);
}