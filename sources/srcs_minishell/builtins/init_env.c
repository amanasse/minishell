/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:57:06 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/15 15:08:34 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

char	**sort_env(char **tab, int size)
{
	char	*tmp;
	int		i;
	int		is_ok;

	i = 0;
	is_ok = 0;
	while (tab && !is_ok)
	{
		is_ok = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				is_ok = 0;
			}
			i++;
		}
		size--;
	}
	return (tab);
}

char	**env_in_tab(t_shell *shell)
{
	int		i;
	char	**tab;
	t_env	*tmp;
	t_env	*tmp2;

	i = 0;
	tmp = shell->environ;
	tmp2 = shell->environ;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (tmp2)
	{
		tab[i] = tmp2->str;
		tmp2 = tmp2->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

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
