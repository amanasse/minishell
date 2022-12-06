/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:44:12 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/06 16:35:22 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_delim(char *str, int i)
{
	int		quote;
	char	*new_str;

	quote = 0;
	new_str = NULL;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
		}
		else if (str[i] == '\'')
		{
			if (quote == 1)
				new_str = ft_stock_str(new_str, str[i]);
		}
		else
			new_str = ft_stock_str(new_str, str[i]);
	}
	if (new_str == NULL)
		new_str = ft_malloc(1);
	return (free(str), new_str);
}

int	heredoc(t_minishell *m)
{
	char	*line;
	char	*tmp;

	m->parse[m->index_cmd].delim = ft_delim(m->parse[m->index_cmd].delim, -1);
	m->fd = open("heredoc.txt", O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (m->fd == -1)
		return (-1);
	while (1)
	{
		line = readline(m->line_heredoc);
		if (line == NULL)
			return (-1);
		if (ft_strcmp(line, m->parse[m->index_cmd].delim) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		if (tmp == NULL)
			return (-1);
		write(m->fd, tmp, ft_strlen(tmp));
		free(tmp);
		free(line);
	}
	return (m->fd);
}

void	exec_heredoc(t_minishell *minishell, int *pipefd)
{
	minishell->fd_heredoc = heredoc(minishell);
	if (minishell->fd_heredoc == -1)
		exit(1);
	close(minishell->fd_heredoc);
	minishell->fd_heredoc = open("heredoc.txt", O_RDONLY);
	if (minishell->index_cmd < minishell->count)
		dup2(pipefd[1], STDOUT_FILENO);
	if (minishell->parse[minishell->index_cmd].fd_out >= 0)
		dup2(minishell->parse[minishell->index_cmd].fd_out, STDOUT_FILENO);
	if (minishell->fd_heredoc >= 0)
		dup2(minishell->fd_heredoc, STDIN_FILENO);
	close(minishell->fd_heredoc);
	if (open("heredoc.txt", O_RDONLY) != -1)
		unlink("heredoc.txt");
}
