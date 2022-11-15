/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:20:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/15 17:29:10 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void	builtins(char **cmd, t_shell *shell)
{
	if ((ft_strcmp(cmd[0], "exit")) == 0)
		shell->status = cmd_exit(cmd);
	if ((ft_strcmp(cmd[0], "pwd")) == 0)
		shell->status = cmd_pwd(cmd, shell);
	if ((ft_strcmp(cmd[0], "cd")) == 0)
		shell->status = cmd_cd(cmd, shell);
	if ((ft_strcmp(cmd[0], "echo")) == 0)
		shell->status = cmd_echo(cmd);
	if ((ft_strcmp(cmd[0], "env")) == 0)
		shell->status = cmd_env(cmd, shell);
	if ((ft_strcmp(cmd[0], "export")) == 0)
		shell->status = cmd_export(cmd, shell);	
	if ((ft_strcmp(cmd[0], "unset")) == 0)
		shell->status = cmd_unset(cmd, shell);
}
