/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:29:14 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/10 18:25:02 by amanasse         ###   ########.fr       */
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

// char	**print_sort_env(t_shell *shell, char **tab)
// {



// 	return (tab);
// }


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
	printf("i = %d\n", i);
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
	i = 0;
	return (tab);	
}


int cmd_export(char **cmd, t_shell *shell)
{
	char **tab;
	int i;

	i = 0;
	if (!cmd[1])
	{	
		tab = env_in_tab(shell);
		while (tab[i])
		{
			printf("[%d] = %s\n", i, tab[i]);
			i++;
		}
		// print_sort_env(shell, tab);
		return (0);
	} 

	printf("DEBUG\n");

	return (0);

	
}