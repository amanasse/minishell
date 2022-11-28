/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:39:30 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/28 13:45:45 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split_paths(t_minishell *minishell, char **split_paths)
{
	minishell->i = 0;
	while (split_paths[minishell->i])
	{
		free(split_paths[minishell->i]);
		minishell->i++;
	}
}

char	*check_path(t_env *environ, t_minishell *minishell)
{
	char	*str;

	str = NULL;
	minishell->shell.status = 1;
	while (environ)
	{
		if (ft_strncmp(environ->str, "PATH", 4) == 0)
		{
			str = environ->str;
			return (str);
		}
		environ = environ->next;
	}
	if (environ == NULL)
		return (NULL);
	return (str);
}

char	*get_path_2(char **split_paths, char **cmd, t_minishell *m)
{
	char	*path;
	char	*path_slash;

	while (split_paths[m->i])
	{
		path_slash = ft_strjoin(split_paths[m->i], "/");
		if (path_slash == NULL)
			return (free_split_paths(m, split_paths), NULL);
		path = ft_strjoin(path_slash, cmd[0]);
		if (path == NULL)
			return (free(path_slash), free_split_paths(m, split_paths), NULL);
		free(path_slash);
		if (access(path, F_OK) == 0)
			return (m->shell.status = 0, path);
		free(path);
		path = NULL;
		m->i++;
	}
	return (NULL);
}

char	*get_path(t_env *environ, char **cmd, t_minishell *minishell)
{
	char	*str;
	char	*path;
	char	**split_paths;

	str = check_path(environ, minishell);
	if (str == NULL)
		return (NULL);
	split_paths = ft_split(str + 5, ':');
	if (split_paths == NULL)
		return (NULL);
	minishell->i = 0;
	path = get_path_2(split_paths, cmd, minishell);
	free_split_paths(minishell, split_paths);
	free(split_paths);
	return (path);
}
