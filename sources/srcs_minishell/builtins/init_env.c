/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:57:06 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/07 15:48:59 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

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

void	env_in_tab(t_minishell *minishell)
{
	int		i;
	t_env	*tmp;
	t_env	*tmp2;

	i = 0;
	tmp = minishell->environ;
	tmp2 = minishell->environ;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	minishell->tab_env = malloc(sizeof(char *) * (i + 1));
	if (minishell->tab_env == NULL)
		return ;
	i = 0;
	while (tmp2)
	{
		minishell->tab_env[i] = tmp2->str;
		tmp2 = tmp2->next;
		i++;
	}
	minishell->tab_env[i] = NULL;
	return ;
}

int	copy_of_env(char **env, t_minishell *minishell)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_lstnew_env(env[i]);
		if (tmp == NULL)
			return (-1);
		ft_lstadd_back_env(&minishell->environ, tmp);
		i++;
	}
	if (minishell->environ == NULL)
	{
		tmp = ft_lstnew_env(ft_strjoin("PWD=", getcwd(NULL, 0)));
		if (tmp == NULL)
			return (-1);
		ft_lstadd_back_env(&minishell->environ, tmp);
		tmp = ft_lstnew_env(ft_strjoin("OLDPWD=", getcwd(NULL, 0)));
		if (tmp == NULL)
			return (-1);
		ft_lstadd_back_env(&minishell->environ, tmp);
	}
	return (0);
}

void	ft_init_all(t_minishell *minishell, char **env, char *prompt)
{
	prompt[0] = '$';
	prompt[1] = '>';
	prompt[2] = ' ';
	prompt[3] = '\0';
	ft_memset(minishell, 0, sizeof(t_minishell));
	g_minishell = minishell;
	copy_of_env(env, minishell);
	minishell->line_heredoc[0] = '>';
	minishell->line_heredoc[1] = ' ';
	minishell->line_heredoc[2] = '\0';
}
