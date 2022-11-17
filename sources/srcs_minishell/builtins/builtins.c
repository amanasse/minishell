/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:20:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/17 16:36:04 by mede-sou         ###   ########.fr       */
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
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		j++;
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		j++;
	return (j);
}

void	builtins(char **cmd, t_minishell *minishell)
{
	if ((ft_strcmp(cmd[0], "exit")) == 0)
		minishell->shell->status = cmd_exit(cmd);
	else if ((ft_strcmp(cmd[0], "export")) == 0)
		minishell->shell->status = cmd_export(cmd, minishell);
	else if ((ft_strcmp(cmd[0], "pwd")) == 0)
		minishell->shell->status = cmd_pwd(cmd, minishell);
	else if ((ft_strcmp(cmd[0], "cd")) == 0)
		minishell->shell->status = cmd_cd(cmd, minishell);
	else if ((ft_strcmp(cmd[0], "echo")) == 0)
		minishell->shell->status = cmd_echo(cmd);
	else if ((ft_strcmp(cmd[0], "env")) == 0)
		minishell->shell->status = cmd_env(cmd, minishell);
	else if ((ft_strcmp(cmd[0], "unset")) == 0)
		minishell->shell->status = cmd_unset(cmd, minishell);
}
