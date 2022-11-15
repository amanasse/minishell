/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:14 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/15 15:09:02 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

int	replace_or_create_var(t_shell *shell, t_export *export, char *str)
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
		ft_lstadd_back_env(&shell->environ, export->element);
	}
	export->is_ok = 0;
	return (0);
}

int	replace_var_env(t_shell *shell, char *str, t_export *export)
{
	while (str && str[export->i] != '=')
		export->i++;
	while (str && str[export->count] != '\0')
		export->count++;
	export->compare = malloc(sizeof(char) * (export->i + 2));
	if (export->compare == NULL)
		return (-1);
	export->compare = ft_strcpy_egal(export->compare, str);
	if (replace_or_create_var(shell, export, str) == -1)
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

int	check_var_env(t_export *export, t_shell *shell, char **cmd)
{
	while (cmd[shell->i])
	{
		export->tmp = shell->environ;
		shell->j = 0;
		while (cmd[shell->i][shell->j])
		{
			if (cmd[shell->i][shell->j] == '=')
				export->var_env = 1;
			shell->j++;
		}
		if (export->var_env == 0)
		{
			export->element = ft_lstnew_env(cmd[shell->i]);
			if (export->element == NULL)
				return (1);
			ft_lstadd_back_env(&shell->environ, export->element);
		}
		else
		{
			if (replace_var_env(shell, cmd[shell->i], export) == -1)
				return (1);
		}
		shell->i++;
	}
	return (0);
}

int	cmd_export(char **cmd, t_shell *shell)
{
	t_export	export;

	shell->i = 0;
	shell->j = 0;
	init_export(&export);
	if (!cmd[1])
	{	
		shell->tab_env = env_in_tab(shell);
		if (shell->tab_env == NULL)
			return (1);
		while (shell->tab_env[shell->i])
			shell->i++;
		sort_env(shell->tab_env, shell->i);
		print_export(shell);
		free (shell->tab_env);
		return (0);
	}
	else
	{
		shell->i = 1;
		if (check_var_env(&export, shell, cmd) == 1)
			return (1);
	}
	return (0);
}
