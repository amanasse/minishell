/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:47:06 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/23 15:47:23 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parse(t_minishell *minishell)
{
	int	i;

	minishell->index_cmd = 0;
	while (minishell->parse[minishell->index_cmd].tab_cmd)
	{
		i = 0;
		while (minishell->parse[minishell->index_cmd].tab_cmd[i])
		{
			free(minishell->parse[minishell->index_cmd].tab_cmd[i]);
			i++;
		}
		free(minishell->parse[minishell->index_cmd].tab_cmd);
		minishell->index_cmd++;
	}
	free(minishell->parse);
	minishell->index_cmd = 0;
	// free(minishell->tab_env);
}