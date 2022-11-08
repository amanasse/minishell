/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:42 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/08 11:48:28 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

char	*search_old_pwd(t_shell *shell)
{
	t_env	*tmp;
	size_t	i;
	char	*srch_old_pwd;

	tmp = shell->environ;
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

int	old_pwd(t_shell *shell)
{
	t_env	*tmp2;
	char	*tmp_pwd;
	char	*old_pwd;

	tmp2 = shell->environ;
	old_pwd = search_old_pwd(shell);
	if (old_pwd == NULL)
		return (-1);
	ft_view_env(shell->environ);
	while (tmp2 != NULL)
	{
		if (ft_strnstr(tmp2->str, "OLDPWD=", 7) == 0)
		{
			tmp_pwd = tmp2->str;
			tmp2->str = old_pwd;
			shell->old_pwd = tmp2->str;
			free (tmp_pwd);
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

int	new_pwd(t_shell *shell, char *dir)
{
	t_env	*tmp;
	size_t	i;
	char	*tmp_pwd;

	i = ft_strlen(dir) + 5;
	tmp = shell->environ;
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
			shell->pwd = tmp->str;
			free(tmp_pwd);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*go_home(t_env *tmp)
{
	char	*dir;

	while (tmp != NULL)
	{
		if (ft_strnstr(tmp->str, "HOME=", 5) == 0)
			dir = tmp->str + 5;
		tmp = tmp->next;
	}
	return (dir);
}

int	*cmd_cd(char **cmd, t_shell *shell)
{
	int		t;
	int		i;
	char	*dir;

	t = 0;
	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		dir = go_home(shell->environ);
	else if (i == 2 && (ft_strcmp(cmd[1], "~")) == 0)
		dir = go_home(shell->environ);
	else
		dir = cmd[1];
	t = chdir(dir);
	if (t == 0)
	{
		dir = getcwd(NULL, 0);
		old_pwd(shell);
		new_pwd(shell, dir);
		free(dir);
	}
	else
		printf("\nError : Directory change failed.\n");
	return (0);
}
