/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:14 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/14 10:30:22 by amanasse         ###   ########.fr       */
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


int cmd_export(char **cmd, t_shell *shell)
{
	char **tab;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!cmd[1])
	{	
		tab = env_in_tab(shell);
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
				if(tab[i][j] == '=')
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
		while (cmd[i])
		{
			ft_lstadd_back_env(&shell->environ, ft_lstnew_env(cmd[i]));
			i++;
		}







		
	}


	return (0);

	
}