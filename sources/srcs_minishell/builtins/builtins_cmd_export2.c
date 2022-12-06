/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_export2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:00:00 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/06 16:53:56 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	concataine_var(t_export *ex, char *str)
{
	char	*tmp;

	ex->l = 0;
	while (ex->tmp != NULL)
	{
		if (ft_strnstr(ex->tmp->str, ex->compare, ex->i) == 0)
		{
			ex->l = count_str(str);
			if (str[ex->l] != ' ')
			{
				tmp = ex->tmp->str;
				ex->tmp->str = ft_strjoin(ex->tmp->str, str + ex->l);
				if (ex->tmp->str == NULL)
					return (-1);
				free(tmp);
			}
		}
		ex->tmp = ex->tmp->next;
	}
	return (0);
}

int	check_if_var_exist(char *str, t_minishell *ms)
{
	t_env	*tmp;
	char	*compare;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	compare = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] != '=' && str[i])
	{
		compare[i] = str[i];
		i++;
	}
	compare[i] = '\0';
	tmp = ms->environ;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, compare, i) == 0)
			return (free(compare), -1);
		tmp = tmp->next;
	}
	return (free(compare), 0);
}

int	count_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '=')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

void	print_export(t_minishell *ms)
{
	int		i;
	int		j;
	int		equal;

	i = 0;
	while (ms->tab_env[i])
	{
		equal = 0;
		j = 0;
		write(ms->fd, "declare -x ", 11);
		while (ms->tab_env[i][j])
		{
			ft_putchar_fd(ms->tab_env[i][j], ms->fd);
			if (ms->tab_env[i][j] == '=' && ms->tab_env[i][j + 1] != '\0')
			{
				equal = 1;
				write(ms->fd, "\"", 1);
			}
			j++;
		}
		if (equal == 1)
			write(ms->fd, "\"", 1);
		write(ms->fd, "\n", 1);
		i++;
	}
}

void	init_export(t_export *export)
{
	export->k = 1;
	export->var_env = 0;
	export->is_ok = 0;
	export->count = 0;
	export->i = 0;
	export->compare = NULL;
}
