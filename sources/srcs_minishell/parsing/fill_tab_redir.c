/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:49:00 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/07 14:31:56 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_file_exists(t_parse *parse, int j)
{
	int	i;

	i = 0;
	if (j == 0)
		return (0);
	while (j > 0)
	{
		if (parse[j].file_in)
		{
			i = 0;
			while (i < j)
			{
				if (ft_strcmp(parse[j].file_in, parse[i].file_in) == 0)
					return (1);
				i++;
			}
		}
		j--;
	}
	return (0);
}

void	redir_r(t_minishell *ms, t_lstms *temp, int j)
{
	int		k;
	char	*tmp;

	if (ms->parse[j].file_in)
		free(ms->parse[j].file_in);
	ms->parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
	ms->parse[j].fd_in = STDIN_FILENO;
	ms->parse[j].fd_out = open(ms->parse[j].file_in, O_WRONLY | O_CREAT, 0644);
	ms->fd = ms->parse[j].fd_out;
	if (ft_check_if_file_exists(ms->parse, j) == 1)
		ms->parse[j].file_already_exists = 1;
	if (ms->parse[j].file_already_exists == 1)
	{
		k = j;
		while (k >= 0)
		{
			if (ms->parse[j].tab_cmd[k])
			{
				tmp = ms->parse[j].tab_cmd[k];
				ms->parse[j].tab_cmd[k] = ft_calloc(1, 1);
				free(tmp);
			}
			k--;
		}
	}
}

void	redir_l(t_minishell *ms, t_lstms *temp, int j)
{
	if (ms->parse[j].file_in)
		free(ms->parse[j].file_in);
	ms->parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
	ms->parse[j].fd_in = open(ms->parse[j].file_in, O_RDONLY, 0644);
	ms->parse[j].fd_out = STDOUT_FILENO;
}

void	ft_fill_parse_redir_l_r(t_minishell *ms, t_lstms *temp, int j, int i)
{
	if (temp->type == REDIR_L)
		redir_l(ms, temp, j);
	else if (temp->type == REDIR_R)
		redir_r(ms, temp, j);
	free(temp->str);
	ms->parse[j].tab_cmd[i] = ft_calloc(1, 1);
}

void	ft_fill_parse(t_minishell *ms, t_lstms *temp, int j, int i)
{
	ms->parse[j].tab_cmd[i] = temp->str;
	ms->parse[j].type = temp->type;
	if (temp->type == REDIR_L || temp->type == REDIR_R)
		ft_fill_parse_redir_l_r(ms, temp, j, i);
	else if (temp->type == HEREDOC)
	{
		ms->if_heredoc = 1;
		ms->parse[j].fd_in = STDIN_FILENO;
		ms->parse[j].fd_out = STDOUT_FILENO;
		ms->parse[j].delim = ft_strncpy(temp->str, ft_strlen(temp->str));
		free(temp->str);
		ms->parse[j].tab_cmd[i] = ft_calloc(1, 1);
	}
	else if (temp->type == APPEND)
	{
		ms->parse[j].fd_in = STDIN_FILENO;
		ms->parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
		free(temp->str);
		ms->parse[j].fd_out = open(ms->parse[j].file_in, O_WRONLY
				| O_APPEND | O_CREAT, 0644);
		ms->parse[j].tab_cmd[i] = ft_calloc(1, 1);
	}
}
