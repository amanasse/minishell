/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:49:00 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/05 11:53:19 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_r(t_minishell *ms, t_lstms *temp, int j)
{
	int	k;

	ms->parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
	ms->parse[j].fd_in = STDIN_FILENO;
	ms->parse[j].fd_out = open(ms->parse[j].file_in, O_WRONLY | O_CREAT, 0644);
	if (ms->parse[j].fd_out == -1)
		printf("minishell: %s: No such file or directory\n", temp->str);
	free(temp->str);
	if (ft_check_if_file_exists(ms->parse, j) == 1)
		ms->parse[j].file_already_exists = 1;
	if (ms->parse[j].file_already_exists == 1)
	{
		k = j;
		while (k >= 0)
		{
			ms->parse[j].tab_cmd[k] = ft_calloc(1, 1);
			k--;
		}
	}
}

void	redir_l(t_minishell *ms, t_lstms *temp, int j)
{
	ms->parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
	ms->parse[j].fd_in = open(ms->parse[j].file_in, O_RDONLY, 0644);
	if (ms->parse[j].fd_in == -1)
		printf("minishell: %s: No such file or directory\n", temp->str);
	free(temp->str);
	ms->parse[j].fd_out = STDOUT_FILENO;
}

void	ft_fill_parse_redir_l_r(t_minishell *ms, t_lstms *temp, int j, int i)
{
	if (temp->type == REDIR_L)
		redir_l(ms, temp, j);
	else if (temp->type == REDIR_R)
		redir_r(ms, temp, j);
	ms->parse[j].tab_cmd[i] = ft_calloc(1, 1);
}
