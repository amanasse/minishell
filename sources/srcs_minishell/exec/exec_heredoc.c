/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:44:12 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/01 16:17:58 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_clean_if_quotes_delim(char *str, int i)
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
	return (new_str);
}

int	heredoc(t_minishell *mini)
{
	int		fd;
	char	*line;
	char	*tmp;

	mini->parse[mini->index_cmd].delim
		= ft_clean_if_quotes_delim(mini->parse[mini->index_cmd].delim, -1);
	fd = open("heredoc.txt", O_WRONLY | O_TRUNC
			| O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline(mini->line_heredoc);
		if (line == NULL)
			return (-1);
		if (ft_strcmp(line,
				mini->parse[mini->index_cmd].delim) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		if (tmp == NULL)
			return (-1);
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
		free(line);
	}
	return (fd);
}

char	**new_cmd_heredoc(t_minishell *minishell, char **cmd)
{
	int		i;
	char	**new_cmd;

	(void)minishell;
	i = 0;
	while (cmd[i])
		i++;
	new_cmd = malloc(sizeof(char *) * (i + 1));
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
	new_cmd[i] = NULL;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	return (new_cmd);
}
