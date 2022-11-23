/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:05:50 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/23 17:00:16 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_new_tab_cmd(t_minishell *minishell)
{
	char	**new_tab_cmd;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (minishell->parse[minishell->index_cmd].tab_cmd[i])
		i++;
	new_tab_cmd = malloc(sizeof(char *) * i + 1);
	if (new_tab_cmd == NULL)
		return (NULL);
	while (k < i && j < i)
	{
		if (minishell->parse[minishell->index_cmd].tab_cmd[k][0] == '\0')
			k++;
		else
		{
			new_tab_cmd[j] = 
				ft_strdup(minishell->parse[minishell->index_cmd].tab_cmd[k]);
			if (new_tab_cmd[j] == NULL)
				return (NULL);
			k++;
			j++;
		}
	}
	new_tab_cmd[j] = NULL;
	return (new_tab_cmd);
}

void	exec_redirection(t_minishell *minishell)
{
	char	**cmd;
	char	*path;
	
	cmd = make_new_tab_cmd(minishell);
	if (minishell->parse[minishell->index_cmd].delimiter != NULL)
		cmd = exec_heredoc(minishell, cmd);
	if (minishell->parse[minishell->index_cmd].fd_out == - 1
		|| minishell->parse[minishell->index_cmd].fd_in == - 1)
	{
		printf("bash: %s: No such file or directory\n",
		minishell->parse[minishell->index_cmd].file_in);
		exit(1);
	}
	if (minishell->parse[minishell->index_cmd].fd_out > 0)
		dup2(minishell->parse[minishell->index_cmd].fd_out, STDOUT);
	if (minishell->parse[minishell->index_cmd].fd_in > 0)
		dup2(minishell->parse[minishell->index_cmd].fd_in, STDIN);
	if ((path = get_path(minishell->environ, cmd)) == NULL)
	{
		printf("%s: command not found\n", cmd[0]);
		exit(1);
	}
	minishell->shell.status = execve(path, cmd, minishell->tab_env);
}
