/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:20:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/22 10:40:35 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	check_builtins(char **cmd)
{
	int	j;

	j = 0;
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		j++;
	return (j);
}

int	check_builtins_env(char **cmd)
{
	int	j;

	j = 0;
	if (ft_strncmp(cmd[0], "cd", 2) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		j++;
	return (j);
}

void	builtins(t_minishell *minishell)
{
	if ((ft_strcmp(minishell->parse[minishell->index_cmd].tab_cmd[0], "exit")) == 0)
		minishell->shell.status = cmd_exit(minishell->parse[minishell->index_cmd].tab_cmd);
	else if ((ft_strcmp(minishell->parse[minishell->index_cmd].tab_cmd[0], "export")) == 0)
		minishell->shell.status = cmd_export(minishell);
	else if ((ft_strcmp(minishell->parse[minishell->index_cmd].tab_cmd[0], "pwd")) == 0)
		minishell->shell.status = cmd_pwd(minishell->parse[minishell->index_cmd].tab_cmd, minishell);
	else if ((ft_strcmp(minishell->parse[minishell->index_cmd].tab_cmd[0], "cd")) == 0)
		minishell->shell.status = cmd_cd(minishell->parse[minishell->index_cmd].tab_cmd, minishell);
	else if ((ft_strcmp(minishell->parse[minishell->index_cmd].tab_cmd[0], "echo")) == 0)
		minishell->shell.status = cmd_echo(minishell->parse[minishell->index_cmd].tab_cmd);
	else if ((ft_strcmp(minishell->parse[minishell->index_cmd].tab_cmd[0], "env")) == 0)
		minishell->shell.status = cmd_env(minishell->parse[minishell->index_cmd].tab_cmd, minishell);
	else if ((ft_strcmp(minishell->parse[minishell->index_cmd].tab_cmd[0], "unset")) == 0)
		minishell->shell.status = cmd_unset(minishell->parse[minishell->index_cmd].tab_cmd, minishell);
}
