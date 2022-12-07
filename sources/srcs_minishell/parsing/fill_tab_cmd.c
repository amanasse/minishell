/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:29:36 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/07 12:28:54 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_tab_cmd(t_lstms *temp, t_minishell *ms)
{
	ms->k = 0;
	while (temp != NULL)
	{
		ms->i_parse = 0;
		ms->nb_cmd = ft_count_cmd(temp);
		ms->parse[ms->k].file_already_exists = 0;
		ms->parse[ms->k].tab_cmd = malloc(sizeof(char *) * (ms->nb_cmd + 1));
		if (ms->parse[ms->k].tab_cmd == NULL)
			return ;
		while (temp->type != PIPE && temp != NULL)
		{
			ft_fill_parse(ms, temp, ms->k, ms->i_parse);
			if (temp->type == HEREDOC)
				ms->fd_heredoc = -1;
			ms->i_parse++;
			temp = temp->next;
			if (temp == NULL)
				break ;
		}
		ms->parse[ms->k].tab_cmd[ms->i_parse] = NULL;
		if (temp != NULL)
			temp = temp->next;
		ms->k++;
	}
	ms->parse[ms->k].tab_cmd = NULL;
}
