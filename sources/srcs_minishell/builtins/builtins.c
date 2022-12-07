/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:20:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/07 15:50:04 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	check_builtins(char **cmd, t_minishell *minishell)
{
	int	j;

	minishell->if_builtins = 0;
	j = 0;
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		j++;
	minishell->if_builtins = j;
	return (j);
}

int	check_builtins_env(char **cmd, t_minishell *minishell)
{
	int		j;
	char	*path;

	j = 0;
	minishell->if_builtins = 0;
	if (ft_strncmp(cmd[0], "cd", 2) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		j++;
	path = get_path(minishell->environ, cmd, minishell);
	if (path)
		free(path);
	minishell->if_builtins = j;
	return (j);
}

void	builtins(t_minishell *m)
{
	if ((ft_strcmp(m->parse[m->index_cmd].tab_cmd[0], "exit")) == 0)
	{
		m->shell.status = cmd_exit(m->parse[m->index_cmd].tab_cmd);
		free_parse(m);
		free(m->tab_env);
		exit(m->shell.status);
	}
	else if ((ft_strcmp(m->parse[m->index_cmd].tab_cmd[0], "export")) == 0)
		m->shell.status = cmd_export(m);
	else if ((ft_strcmp(m->parse[m->index_cmd].tab_cmd[0], "pwd")) == 0)
		m->shell.status = cmd_pwd(m->parse[m->index_cmd].tab_cmd, m);
	else if ((ft_strcmp(m->parse[m->index_cmd].tab_cmd[0], "cd")) == 0)
		m->shell.status = cmd_cd(m->parse[m->index_cmd].tab_cmd, m, 0, 0);
	else if ((ft_strcmp(m->parse[m->index_cmd].tab_cmd[0], "echo")) == 0)
		m->shell.status = cmd_echo(m->parse[m->index_cmd].tab_cmd);
	else if ((ft_strcmp(m->parse[m->index_cmd].tab_cmd[0], "env")) == 0)
		m->shell.status = cmd_env(m->parse[m->index_cmd].tab_cmd, m);
	else if ((ft_strcmp(m->parse[m->index_cmd].tab_cmd[0], "unset")) == 0)
		m->shell.status = cmd_unset(m->parse[m->index_cmd].tab_cmd, m);
}
