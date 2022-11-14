/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:14 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/14 15:08:52 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

//Export remplacer ce quil y a derriere la variable d'environnement OU ajouter completement une variable si celle ci n'existe pas.
//Exemple : export PWD=MDRRRRRR --> remplace le chemin de base de PWD dans l'en
// 1. Verifier si la sous commande existe dans l'env.
// 2. Si le chemin est exacte (PWD=). free la str du maillon (puis recreer la nouvelle str a malloc).
// 3. Penser a free egalement les chaines de caracteres a partir du moment ou celles-ci ont ete malloc (PWD et OLD pwd).
// 4. Export le nombre de fois quil y a de commandes. exemple (export PWD=coucou PAGER=ahah doit foncionner pour les 2).
// 5. EXEMPLES : 1 - export PWD=coucou odwokd "kdowkdo" PAGER=ahah doit egalement fonctionner pour les 2 commandes valides.
//               2 - export PWD= doit remplacer la suite par du vide.
//               3 - export JEMAPPELLE=Adrian doit creer la variable dans l'env

char	**print_sort_env(char **tab, int size)
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
	int i;
	char **tab;
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
	tab = malloc(sizeof(char*) * (i + 1));
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
	i = 0;
	return (tab);	
}

int	replace_var_env(t_shell *shell, char *str)
{
	t_env	*tmp;
	int		count;
	int		i;
	char	*compare;
	int 	is_ok;
	
	i = 0;
	is_ok = 0;
	count = 0;
	tmp = shell->environ;
	while (str && str[i] != '=')
		i++;
	while (str && str[count] != '\0')
		count++;
	compare = malloc(sizeof(char) * (i + 2));
	if (compare == NULL)
		return (-1);
	compare = ft_strcpy_egal(compare, str);
	printf ("compare = %s", compare);
	while (tmp)
	{
		if (ft_strnstr(tmp->str, compare, i + 1) == 0)
		{
			free(tmp->str);
			tmp->str = malloc(sizeof(char) * (count + 1));
			if (tmp->str == NULL)
				return (free(compare), -1);
			tmp->str = ft_strcpy(tmp->str, str);
			is_ok = 1;
			free(compare);
		}
		tmp = tmp->next;
	}
	if(is_ok == 0)
		ft_lstadd_back_env(&shell->environ, ft_lstnew_env(str));
	return (0);	
}

int cmd_export(char **cmd, t_shell *shell)
{
	char **tab;
	int i;
	int j;
	int var_env;

	i = 0;
	j = 0;
	var_env = 0;
	if (!cmd[1])
	{	
		tab = env_in_tab(shell);
		if (tab == NULL)
			return (1);
		while (tab[i])
			i++;
		print_sort_env(tab, i);
		i = 0;
		while (tab[i])
		{
			j = 0;
			write (1, "declare -x ", 11);
			while(tab[i][j])
			{
				ft_putchar_fd(tab[i][j], 1);
				if(tab[i][j] == '=' && tab[i][j + 1] != '\0')
					write (1, "\"", 1);
				j++;
			}
			write (1, "\"", 1);
			write (1, "\n", 1);
			i++;
		}
		free (tab);
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
				if(replace_var_env(shell, cmd[i]) == -1)
					return (1);
			}
			i++;
		}







		
	}


	return (0);

	
}