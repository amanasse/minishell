/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:29:36 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/29 13:12:36 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_parse_redir_l_r(t_parse *parse, t_lstms *temp, int j, int i)
{
	parse[j].tab_cmd[i] = temp->str;
	if (temp->type == REDIR_L)
	{
		parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
		parse[j].fd_in = open(temp->str, O_RDONLY, S_IRWXU);
		if (parse[j].fd_in == -1)
			printf("minishell: %s: No such file or directory\n", temp->str);
		parse[j].fd_out = 1;
		parse[j].tab_cmd[i] = ft_calloc(1, 1);
	}
	else if (temp->type == REDIR_R)
	{
		parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
		parse[j].fd_in = 1;
		parse[j].fd_out = open(temp->str, O_WRONLY
				| O_TRUNC | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
		if (parse[j].fd_out == -1)
			printf("minishell: %s: No such file or directory\n", temp->str);
		parse[j].tab_cmd[i] = ft_calloc(1, 1);
	}	
}

void	ft_fill_parse(t_parse *parse, t_lstms *temp, int j, int i)
{
	parse[j].tab_cmd[i] = temp->str;
	if (temp->type == REDIR_L || temp->type == REDIR_R)
		ft_fill_parse_redir_l_r(parse, temp, j, i);
	else if (temp->type == HEREDOC)
	{
		parse[j].if_heredoc = 1;
		parse[j].fd_in = STDIN_FILENO;
		parse[j].fd_out = STDOUT_FILENO;
		parse[j].fd_heredoc = -1;
		parse[j].delim = ft_strncpy(temp->str, ft_strlen(temp->str));
		parse[j].tab_cmd[i] = ft_calloc(1, 1);
	}
	else if (temp->type == APPEND)
	{
		parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
		parse[j].fd_in = 1;
		parse[j].fd_out = open(temp->str, O_WRONLY
				| O_APPEND | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
		if (parse[j].fd_out == -1)
			printf("minishell: %s: No such file or directory\n", temp->str);
		parse[j].tab_cmd[i] = ft_calloc(1, 1);
	}
	parse[j].type = temp->type;
}

void	ft_fill_tab_cmd(t_lstms *temp, t_minishell *ms)
{
	int		j;
	int		nb_cmd;

	j = 0;
	while (temp != NULL)
	{
		ms->i_parse = 0;
		nb_cmd = ft_count_cmd(temp);
		ms->parse[j].tab_cmd = malloc(sizeof(char *) * (nb_cmd + 1));
		if (ms->parse[j].tab_cmd == NULL)
			return ;
		while (temp->type != PIPE && temp != NULL)
		{
			ft_fill_parse(ms->parse, temp, j, ms->i_parse);
			ms->i_parse++;
			temp = temp->next;
			if (temp == NULL)
				break ;
		}
		ms->parse[j].tab_cmd[ms->i_parse] = NULL;
		if (temp != NULL)
			temp = temp->next;
		j++;
	}
	ms->parse[j].tab_cmd = NULL;
}
