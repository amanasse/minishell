/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:14 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/25 13:26:33 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	replace_or_create_var(t_minishell *ms, t_export *export, char *str)
{
	while (export->tmp != NULL)
	{
		if (ft_strnstr(export->tmp->str, export->compare, export->i + 1) == 0)
		{
			free(export->tmp->str);
			export->tmp->str = malloc(sizeof(char) * (export->count + 1));
			if (export->tmp->str == NULL)
				return (free(export->compare), -1);
			export->tmp->str = ft_strcpy(export->tmp->str, str);
			export->is_ok = 1;
		}
		export->tmp = export->tmp->next;
	}
	if (export->is_ok == 0)
	{
		export->element = ft_lstnew_env(str);
		if (export->element == NULL)
			return (-1);
		ft_lstadd_back_env(&ms->environ, export->element);
	}
	export->is_ok = 0;
	return (0);
}

int	replace_var_env(t_minishell *ms, char *str, t_export *export)
{
	while (str && str[export->i] != '=')
		export->i++;
	while (str && str[export->count] != '\0')
		export->count++;
	export->compare = malloc(sizeof(char) * (export->i + 2));
	if (export->compare == NULL)
		return (-1);
	export->compare = ft_strcpy_egal(export->compare, str);
	if (replace_or_create_var(ms, export, str) == -1)
		return (free(export->compare), -1);
	return (free(export->compare), 0);
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

int	check_var_env(t_export *export, t_minishell *ms, char **cmd)
{
	while (cmd[export->k])
	{
		export->tmp = ms->environ;
		export->j = 0;
		while (cmd[export->k][export->j])
		{
			if (cmd[export->k][export->j] == '=')
				export->var_env = 1;
			export->j++;
		}
		if (export->var_env == 0)
		{
			export->element = ft_lstnew_env(cmd[export->k]);
			if (export->element == NULL)
				return (1);
			ft_lstadd_back_env(&ms->environ, export->element);
		}
		else
		{
			if (replace_var_env(ms, cmd[export->k], export) == -1)
				return (1);
		}
		export->k++;
	}
	return (0);
}

int	cmd_export(t_minishell *m)
{
	t_export	export;
	int			i;
	int			type;

	i = 0;
	init_export(&export);
	type = m->parse[m->index_cmd].type;
	printf("type = %d\n", type);
	if (type == REDIR_L || type == REDIR_R || type == APPEND
		|| !m->parse[m->index_cmd].tab_cmd[1])
	{	
		while (m->tab_env[i])
			i++;
		sort_env(m->tab_env, i);
		print_export(m);
		free(m->tab_env);
		m->tab_env = NULL;
	}
	else
	{
		if (check_var_env(&export, m, m->parse[m->index_cmd].tab_cmd) == 1)
			return (1);
	}
	return (0);
}
