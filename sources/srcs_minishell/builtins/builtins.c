/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:20:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/07 14:20:47 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void	builtins(char **cmd, t_shell *shell)
{
	if ((ft_strcmp(cmd[0], "exit")) == 0)
		cmd_exit(cmd);
	if ((ft_strcmp(cmd[0], "pwd")) == 0)
		cmd_pwd(cmd, shell);
	if ((ft_strcmp(cmd[0], "cd")) == 0)	
		cmd_cd(cmd, shell);
	if ((ft_strcmp(cmd[0], "echo")) == 0)
		cmd_echo(cmd);
}
