/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:29:36 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/02 12:56:25 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_parse_redir_l_r(t_minishell *ms, t_lstms *temp, int j, int i)
{
	ms->parse[j].tab_cmd[i] = temp->str;
	if (temp->type == REDIR_L)
	{
		if (ms->parse[j].file_in)
			free(ms->parse[j].file_in);
		ms->parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
		free(temp->str);
		ms->parse[j].fd_in = open(ms->parse[j].file_in, O_RDONLY, 0644);
		if (ms->parse[j].fd_in == -1)
			printf("minishell: %s: No such file or directory\n", temp->str);
		ms->parse[j].fd_out = STDOUT_FILENO;
		ms->parse[j].tab_cmd[i] = ft_calloc(1, 1);
	}
	else if (temp->type == REDIR_R)
	{
		if (ms->parse[j].file_in)
			free(ms->parse[j].file_in);
		ms->parse[j].fd_in = STDIN_FILENO;
		ms->parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
		free(temp->str);
		ms->parse[j].fd_out = open(ms->parse[j].file_in, O_WRONLY | O_CREAT, 0644);
		if (ms->parse[j].fd_out == -1)
			printf("minishell: %s: No such file or directory\n", temp->str);
		ms->filename = ms->parse[j].file_in;
		ms->fd = ms->parse[j].fd_out;
		ms->parse[j].tab_cmd[i] = ft_calloc(1, 1);
	}	
}

void	ft_fill_parse(t_minishell *ms, t_lstms *temp, int j, int i)
{
	ms->parse[j].tab_cmd[i] = temp->str;
	if (temp->type == REDIR_L || temp->type == REDIR_R)
		ft_fill_parse_redir_l_r(ms, temp, j, i);
	else if (temp->type == HEREDOC)
	{
		ms->parse[j].if_heredoc = 1;
		ms->parse[j].fd_in = STDIN_FILENO;
		ms->parse[j].fd_out = STDOUT_FILENO;
		ms->parse[j].delim = ft_strncpy(temp->str, ft_strlen(temp->str));
		free(temp->str);
		ms->parse[j].tab_cmd[i] = ft_calloc(1, 1);
	}
	else if (temp->type == APPEND)
	{
		if (ms->parse[j].file_in)
			free(ms->parse[j].file_in);
		ms->parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
		free(temp->str);
		ms->parse[j].fd_in = STDIN_FILENO;
		ms->parse[j].fd_out = open(ms->parse[j].file_in, O_WRONLY
				| O_APPEND | O_CREAT, 0644);
		if (ms->parse[j].fd_out == -1)
			printf("minishell: %s: No such file or directory\n", temp->str);
		ms->parse[j].tab_cmd[i] = ft_calloc(1, 1);
	}
	ms->parse[j].type = temp->type;
}

void	ft_print_struc_parse(t_parse *parse, int k) // a supprimer
{
	int i;
	int	j;

	i = 0;
	while (i < k)
	{
		j = 0;
		while (parse[i].tab_cmd[j] != NULL)
		{
			printf("parse[%d]->file_in = %s\n", i, parse[i].file_in);
			j++;
		}
		i++;
	}
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
			ft_fill_parse(ms, temp, j, ms->i_parse);
			if (temp->type == HEREDOC)
				ms->fd_heredoc = -1;
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
	ft_print_struc_parse(ms->parse, ms->count + 1);
	
}
