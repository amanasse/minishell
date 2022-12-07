/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tab_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:17:05 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/07 14:00:00 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_cmd(t_lstms *lex)
{
	int	count;

	count = 0;
	while (lex != NULL)
	{
		if (lex->type != 2)
			count++;
		lex = lex->next;
	}
	return (count);
}

void	ft_init_struc_parse(t_parse *parse, int i)
{
	parse[i].file_in = NULL;
	parse[i].delim = NULL;
	parse[i].tab_cmd = NULL;
	parse[i].fd_in = 0;
	parse[i].fd_out = 1;
	parse[i].if_heredoc = 0;
	parse[i].if_pipe = 0;
	parse[i].type = 0;
}

void	ft_build_struc_parse(t_minishell *minishell, int count)
{
	t_lstms	*temp;
	int		i;

	temp = minishell->lstms;
	i = 0;
	minishell->parse = malloc(sizeof(t_parse) * (count + 2));
	if (minishell->parse == NULL)
		return ;
	while (minishell->parse && i < (count + 2))
	{	
		ft_init_struc_parse(minishell->parse, i);
		i++;
	}
	ft_fill_tab_cmd(temp, minishell);
}
