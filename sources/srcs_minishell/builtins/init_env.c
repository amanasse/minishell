/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:57:06 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/14 17:29:00 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

int	copy_of_env(char **env, t_shell *shell)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_lstnew_env(env[i]);
		if (tmp == NULL)
			return (-1);
		ft_lstadd_back_env(&shell->environ, tmp);
		i++;
	}
	return (0);
}
