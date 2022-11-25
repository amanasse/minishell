/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_export2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:00:00 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/25 13:23:30 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	init_export(t_export *export)
{
	export->k = 1;
	export->var_env = 0;
	export->is_ok = 0;
	export->count = 0;
	export->i = 0;
	export->compare = NULL;
}
