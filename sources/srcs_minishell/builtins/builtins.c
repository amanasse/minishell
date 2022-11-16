/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:20:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/16 16:16:10 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void	builtins(char **cmd, t_minishell *minishell)
{
	if ((ft_strcmp(cmd[0], "exit")) == 0)
		minishell->shell->status = cmd_exit(cmd);
	if ((ft_strcmp(cmd[0], "pwd")) == 0)
		minishell->shell->status = cmd_pwd(cmd, minishell);
	if ((ft_strcmp(cmd[0], "cd")) == 0)	
		minishell->shell->status = cmd_cd(cmd, minishell);
	if ((ft_strcmp(cmd[0], "echo")) == 0)
		minishell->shell->status = cmd_echo(cmd);
	if ((ft_strcmp(cmd[0], "env")) == 0)
		minishell->shell->status = cmd_env(cmd, minishell);
	if ((ft_strcmp(cmd[0], "export")) == 0)
		minishell->shell->status = cmd_export(cmd, minishell);
	if ((ft_strcmp(cmd[0], "unset")) == 0)
		minishell->shell->status = cmd_unset(cmd, minishell);
}
