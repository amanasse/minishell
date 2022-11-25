/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:47:06 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/25 12:03:55 by amanasse         ###   ########.fr       */
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
}

void	control_d_or_clear(char *str, t_minishell *minishell)
{
	if (str == NULL)
	{
		write(1, "exit\n", 5);
		free (str);
		free_parse(minishell);
		ft_lstclear_ms(minishell->lstms);
		ft_lstclear_env(minishell->environ);
		exit (0);
	}
	else
	{
		free_parse(minishell);
		ft_lstclear_ms(minishell->lstms);
		free(str);
	}
}
