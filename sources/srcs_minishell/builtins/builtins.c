/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:20:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/03 15:58:58 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void	builtins(char **cmd, t_env *c_env)
{
	if ((ft_strcmp(cmd[0], "exit")) == 0)
		cmd_exit(cmd);
	if ((ft_strcmp(cmd[0], "pwd")) == 0)
		cmd_pwd(cmd, c_env);
	if ((ft_strcmp(cmd[0], "cd")) == 0)
		cmd_cd(cmd, c_env);
	if ((ft_strcmp(cmd[0], "echo")) == 0)
		cmd_echo(cmd);
}
