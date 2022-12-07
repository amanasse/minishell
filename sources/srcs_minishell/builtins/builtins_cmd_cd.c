/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:42 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/07 15:50:38 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

char	*search_old_pwd(t_minishell *minishell)
{
	t_env	*tmp;
	size_t	i;
	char	*srch_old_pwd;

	tmp = minishell->environ;
	srch_old_pwd = NULL;
	while (tmp != NULL)
	{
		if (ft_strnstr(tmp->str, "PWD=", 4) == 0)
		{
			i = ft_strlen(tmp->str) + 3;
			srch_old_pwd = malloc(sizeof(char) * i + 1);
			if (srch_old_pwd == NULL)
				return (NULL);
			srch_old_pwd = strcpy(srch_old_pwd, "OLDPWD=");
			srch_old_pwd = ft_strcat_mini(srch_old_pwd, tmp->str + 4);
			break ;
		}
		tmp = tmp->next;
	}
	return (srch_old_pwd);
}

int	old_pwd(t_minishell *minishell)
{
	t_env	*tmp2;
	char	*tmp_pwd;
	char	*old_pwd;

	tmp2 = minishell->environ;
	old_pwd = search_old_pwd(minishell);
	if (old_pwd == NULL)
		return (-1);
	while (tmp2 != NULL)
	{
		if (ft_strnstr(tmp2->str, "OLDPWD=", 7) == 0)
		{
			tmp_pwd = tmp2->str;
			tmp2->str = old_pwd;
			minishell->shell.old_pwd = tmp2->str;
			free (tmp_pwd);
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

int	new_pwd(t_minishell *minishell, char *dir)
{
	t_env	*tmp;
	size_t	i;
	char	*tmp_pwd;

	i = ft_strlen(dir) + 5;
	tmp = minishell->environ;
	while (tmp != NULL)
	{
		if (ft_strnstr(tmp->str, "PWD=", 4) == 0)
		{
			tmp_pwd = tmp->str;
			tmp->str = malloc(sizeof(char) * i + 1);
			if (tmp->str == NULL)
				return (-1);
			tmp->str = strcpy(tmp->str, "PWD=");
			tmp->str = ft_strcat_mini(tmp->str, dir);
			minishell->shell.pwd = tmp->str;
			free(tmp_pwd);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*go_home(t_minishell *minishell)
{
	char	*dir;
	t_env	*tmp;

	dir = NULL;
	tmp = minishell->environ;
	while (tmp != NULL)
	{
		if (ft_strnstr(tmp->str, "HOME=", 5) == 0)
			dir = tmp->str + 5;
		tmp = tmp->next;
	}
	return (dir);
}

int	cmd_cd(char **cmd, t_minishell *minishell, int t, int i)
{
	char	*dir;

	while (cmd[i])
		i++;
	if (i == 1)
		dir = go_home(minishell);
	else if (i == 2 && (ft_strcmp(cmd[1], "~")) == 0)
		dir = go_home(minishell);
	else
		dir = cmd[1];
	if (dir == NULL)
		return (0);
	t = chdir(dir);
	if (t == 0)
	{
		dir = getcwd(NULL, 0);
		old_pwd(minishell);
		new_pwd(minishell, dir);
		free(dir);
	}
	else
		return (printf("Error: Directory change failed.\n"), 1);
	return (0);
}
