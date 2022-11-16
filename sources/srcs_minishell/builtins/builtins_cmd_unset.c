/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:17 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/15 17:36:52 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"


void	init_unset(t_unset *unset)
{
	unset->i = 1;
	unset->var_env = 0;
	unset->is_ok = 0;
	unset->count = 0;
}

int	cmd_unset(char **cmd, t_shell *shell)
{
    t_unset unset;

    if (cmd[1])
    {
	    init_unset(&unset);
        while (cmd[unset.i])
        {

            if ()




            unset.i++;
        }



        
    }






    return (0);
}