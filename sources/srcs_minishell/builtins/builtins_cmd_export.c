/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:14 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/15 12:42:06 by amanasse         ###   ########.fr       */
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

int	replace_or_create_var(t_shell *shell, t_export *export, char *str)
{
	while (export->tmp)
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
	return (0);
}

int	replace_var_env(t_shell *shell, char *str)
{
	t_export	export;

	init_export(&export, shell);
	while (str && str[export.i] != '=')
		export.i++;
	while (str && str[export.count] != '\0')
		export.count++;
	export.compare = malloc(sizeof(char) * (export.i + 2));
	if (export.compare == NULL)
		return (-1);
	export.compare = ft_strcpy_egal(export.compare, str);
	if (replace_or_create_var(shell, &export, str) == -1)
		return (-1);
	return (0);
}

int	cmd_export(char **cmd, t_shell *shell)
{
	int		i;
	int		j;
	int		var_env;

	i = 0;
	j = 0;
	var_env = 0;
	if (!cmd[1])
	{	
		shell->tab_env = env_in_tab(shell);
		if (shell->tab_env == NULL)
			return (1);
		while (shell->tab_env[i])
			i++;
		sort_env(shell->tab_env, i);
		i = 0;
		while (shell->tab_env[i])
		{
			j = 0;
			write (1, "declare -x ", 11);
			while (shell->tab_env[i][j])
			{
				ft_putchar_fd(shell->tab_env[i][j], 1);
				if (shell->tab_env[i][j] == '=' && shell->tab_env[i][j + 1] != '\0')
					write (1, "\"", 1);
				j++;
			}
			write (1, "\"", 1);
			write (1, "\n", 1);
			i++;
		}
		free (shell->tab_env);
		return (0);
	}
	else
	{
		i = 1;
		while (cmd[i])
		{
			j = 0;
			while (cmd[i][j])
			{
				if (cmd[i][j] == '=')
					var_env = 1;
				j++;
			}
			if (var_env == 0)
				ft_lstadd_back_env(&shell->environ, ft_lstnew_env(cmd[i]));
			else
			{
				if (replace_var_env(shell, cmd[i]) == -1)
					return (1);
			}
			i++;
		}
	}
	return (0);
}
