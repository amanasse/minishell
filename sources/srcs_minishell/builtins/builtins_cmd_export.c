/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:14 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/05 10:25:29 by amanasse         ###   ########.fr       */
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
	if (str[export->i - 1] == '+')
	{
		free(export->compare);
		export->compare = NULL;
		export->compare = ft_strcpy_concataine(str);
		if (concataine_var(export, str) == -1)
			return (free(export->compare), -1);
	}
	else
	{
		if (replace_or_create_var(ms, export, str) == -1)
			return (free(export->compare), -1);
	}
	return (free(export->compare), 0);
}

int	add_var(char **cmd, t_export *ex, t_minishell *ms)
{
	if (check_if_var_exist(cmd[ex->k], ms) == 0)
	{
		ex->element = ft_lstnew_env(cmd[ex->k]);
		if (ex->element == NULL)
			return (1);
		ft_lstadd_back_env(&ms->environ, ex->element);
	}
	return (0);
}

int	check_var_env(t_export *ex, t_minishell *ms, char **cmd)
{
	while (cmd[ex->k])
	{
		ex->tmp = ms->environ;
		ex->j = 0;
		if (cmd[ex->k][0] == '\0')
			return (printf("minishell: export: not a valid identifier\n"), 1);
		while (cmd[ex->k][ex->j])
		{
			if (cmd[ex->k][ex->j] == '=' && ex->j > 0 && cmd[ex->k][0] != '+')
				ex->var_env = 1;
			ex->j++;
		}
		if (ex->var_env == 0)
		{
			if (add_var(cmd, ex, ms) == 1)
				return (1);
		}
		else
		{
			if (replace_var_env(ms, cmd[ex->k], ex) == -1)
				return (1);
		}
		ex->k++;
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
