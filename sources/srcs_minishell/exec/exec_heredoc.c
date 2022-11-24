/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:44:12 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/24 17:37:48 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_minishell *minishell)
{
	int		fd;
	char	line_heredoc[3];
	char	*line;
	char	*tmp;

	line_heredoc[0] = '>';
	line_heredoc[1] = ' ';
	line_heredoc[2] = '\0';
	fd = open("heredoc.txt", O_RDWR | O_CREAT | O_TRUNC,
		S_IRWXU, S_IRGRP, S_IROTH);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline(line_heredoc);
		if (line == NULL)
			return (-1);
		if (ft_strcmp(line,
			minishell->parse[minishell->index_cmd].delimiter) == 0)
			break ;
		tmp = ft_strjoin(line, "\n");
		if (tmp == NULL)
			return (-1);
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
		free(line);
	}
	printf("fd = %d\n", fd);
	return (fd);
}

char	**exec_heredoc(t_minishell *minishell, char **cmd)
{
	int		fd;
	int		i;
	char	**new_cmd;

	i = 0;
	fd = heredoc(minishell);
	if (fd == -1)
		exit(1);
	minishell->parse[minishell->index_cmd].fd_in = fd;
	while (cmd[i])
		i++;
	new_cmd = malloc(sizeof(char *) * i + 1);
	if (new_cmd == NULL)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		new_cmd[i] = ft_strdup(cmd[i]);
		if (new_cmd[i] == NULL)
			return (NULL);
		i++;
	}
	new_cmd[i] = ft_strdup("heredoc.txt");
	if (new_cmd[i] == NULL)
		return (NULL);
	i++;
	new_cmd[i] = NULL;
	free(cmd);
	return (new_cmd);
}