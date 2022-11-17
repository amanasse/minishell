/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_export2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:00:00 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/17 14:34:20 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void	init_export(t_export *export)
{
	export->var_env = 0;
	export->is_ok = 0;
	export->count = 0;
	export->i = 0;
	export->compare = NULL;
}
