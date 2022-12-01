/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:47:06 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/01 11:38:23 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parse(t_minishell *minishell)
{
	int	i;

	minishell->index_cmd = 0;
	while (minishell->index_cmd <= minishell->count)
	{
		if (minishell->parse[minishell->index_cmd].delim)
			free(minishell->parse[minishell->index_cmd].delim);
		if (minishell->parse[minishell->index_cmd].file_in)
			free(minishell->parse[minishell->index_cmd].file_in);
		minishell->index_cmd++;
	}
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
	if (minishell->parse)
		free(minishell->parse);
	minishell->parse = NULL;
	minishell->index_cmd = 0;
}

void	control_d_or_clear(char *str, t_minishell *minishell)
{
	if (str == NULL)
	{
		write(1, "exit\n", 5);
		free(str);
		if (minishell->parse)
			free_parse(minishell);
		if (minishell->lstms)
			ft_lstclear_ms(minishell->lstms);
		if (minishell->environ)
			ft_lstclear_env(minishell->environ);
		exit (0);
	}
	else
	{
		if (minishell->parse)
			free_parse(minishell);
		if (minishell->lstms)
			ft_lstclear_ms(minishell->lstms);
		if (str)
			free(str);
	}
}
