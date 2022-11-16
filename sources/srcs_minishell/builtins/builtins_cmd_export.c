/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:14 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/16 12:07:54 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

int	replace_or_create_var(t_env *environ, t_export *export, char *str)
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
			free(export->compare);
		}
		export->tmp = export->tmp->next;
	}
	if (export->is_ok == 0)
	{
		export->element = ft_lstnew_env(str);
		if (export->element == NULL)
			return (-1);
		ft_lstadd_back_env(&environ, export->element);
	}
	export->is_ok = 0;
	return (0);
}

int	replace_var_env(t_env *environ, char *str, t_export *export)
{
	while (str && str[export->i] != '=')
		export->i++;
	while (str && str[export->count] != '\0')
		export->count++;
	export->compare = malloc(sizeof(char) * (export->i + 2));
	if (export->compare == NULL)
		return (-1);
	export->compare = ft_strcpy_egal(export->compare, str);
	if (replace_or_create_var(environ, export, str) == -1)
		return (-1);
	return (0);
}

void	print_export(t_shell *shell)
{
	shell->i = 0;
	while (shell->tab_env[shell->i])
	{
		shell->j = 0;
		write (1, "declare -x ", 11);
		while (shell->tab_env[shell->i][shell->j])
		{
			ft_putchar_fd(shell->tab_env[shell->i][shell->j], 1);
			if (shell->tab_env[shell->i][shell->j] == '='
			&& shell->tab_env[shell->i][shell->j + 1] != '\0')
				write (1, "\"", 1);
			shell->j++;
		}
		write (1, "\"", 1);
		write (1, "\n", 1);
		shell->i++;
	}	
}

int	check_var_env(t_export *export, t_minishell *minishell, char **cmd)
{
	while (cmd[minishell->shell->i])
	{
		export->tmp = minishell->environ;
		minishell->shell->j = 0;
		while (cmd[minishell->shell->i][minishell->shell->j])
		{
			if (cmd[minishell->shell->i][minishell->shell->j] == '=')
				export->var_env = 1;
			minishell->shell->j++;
		}
		if (export->var_env == 0)
		{
			export->element = ft_lstnew_env(cmd[minishell->shell->i]);
			if (export->element == NULL)
				return (1);
			ft_lstadd_back_env(&minishell->environ, export->element);
		}
		else
		{
			if (replace_var_env(minishell->environ, cmd[minishell->shell->i], export) == -1)
				return (1);
		}
		minishell->shell->i++;
	}
	return (0);
}

int	cmd_export(char **cmd, t_minishell *minishell)
{
	t_export	export;

	minishell->shell->i = 0;
	minishell->shell->j = 0;
	init_export(&export);
	if (!cmd[1])
	{	
		minishell->shell->tab_env = env_in_tab(minishell);
		if (minishell->shell->tab_env == NULL)
			return (1);
		while (minishell->shell->tab_env[minishell->shell->i])
			minishell->shell->i++;
		sort_env(minishell->shell->tab_env, minishell->shell->i);
		print_export(minishell->shell);
		free (minishell->shell->tab_env);
		return (0);
	}
	else
	{
		minishell->shell->i = 1;
		if (check_var_env(&export, minishell, cmd) == 1)
			return (1);
	}
	return (0);
}
