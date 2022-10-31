/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:23:23 by amanasse          #+#    #+#             */
/*   Updated: 2022/10/31 10:27:23 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_path(char **env, char *cmd)
{
	char  *path;
	int   i;
	char  *path_slash;
	char  **split_paths;
	
	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 1)
		i++;
	split_paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (split_paths[i])
	{
		path_slash = ft_strjoin(split_paths[i], "/");
		path = ft_strjoin(path_slash, cmd);
		free(path_slash);
		free(split_paths[i]);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (split_paths[i])
	{
		free(split_paths[i]);
		i++;
	}
	free(split_paths);
	return (NULL);
}

int	ft_fork1(char **env, char **cmd, int *pipefd)
{
	pid_t	pid;
	char	*path;
	
	pid = fork();
	if (pid == 0)
	{
		if ((path = get_path(env, cmd[0])) == NULL)
		{
			printf("%s: command not found\n", cmd[0]);
			return (0);
		}
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(path, cmd, env);
	}
	return (1);
}

int	ft_fork2(char **env, char **cmd, int *pipefd)
{
	pid_t	pid;
	char	*path;

	
	pid = fork();
	if (pid == 0)
	{
		if ((path = get_path(env, cmd[0])) == NULL)
		{
			printf("%s: command not found\n", cmd[0]);
			return (0);
		}
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		close(pipefd[0]);
		execve(path, cmd, env);
	}
	return (1);
}
  
int main(int argc, char **argv, char **env)
{
	char  prompt[3] = "$>";
	char  *str;
	char  **cmd;
	int	 *pipefd;
	
	(void)argc;
	(void)argv;

	str = readline(prompt);
	cmd = ft_split(str, '|');
	pipefd = malloc(sizeof(int) * 2);
	while (1)
	{
		cmd = ft_split(cmd[0], ' ');
		if (pipe(pipefd) == -1)
			return (0);
		ft_fork1(env, cmd, pipefd);
		cmd = ft_split(str, '|');
		cmd = ft_split(cmd[1], ' ');
		ft_fork2(env, cmd, pipefd);
		close(pipefd[1]);
		close(pipefd[0]);
		wait(NULL);
		wait(NULL);
		str = readline(prompt);
		add_history(str);
		if (str == NULL)
		{
			free (str);
			exit (0);
		}
		free (str);
	}
	return (0);
}


/*
  ETAPE 3 LANCER UN PROGRAMME - FORKER
  Une fois qu’on a recuperer le path, qu’on sait que c’est le bon, on va
  forker. Pourquoi ? parce qu’apres avoir lancer execve, le programme s’arrete.
  On veut arreter le programme, pas le minishell. Il faut donc duppliquer le
  prog. C’est le role de fork. Le cours explique comment il marche.
  A vous de jouer.
  
*/

/*
  ETAPE 3 LANCER UN PROGRAMME - EXECVE
  execve doit etre execute dans le fils. S’il reussit, alors il ne fera pas ce
  qu’il y a apres puisqu’il quitte. Sinon, il le fera.
  il prend en parametre le path calcule precedemment et un tableau a deux
  dimemsions vers chaque arguments exemple :
  {"ls", "-l", "-a", ".", NULL}
  ca tombe bien, c’est exectement ce qu’on a fait avec le str_to_wordtab.
  et l’environnement sous forme d’un tableau.
*/

/*
  et voila ! On a lance un programme a partir de notre minishell.
  Maintenant, on a quelques builtins a realiser. 
  env, setenv et unsetenv. Le mieux serait de le faire avec des listes
  chainees. Je vous ai appris a en faire dans un precedent cours.
  Si vous n’etes pas a l’aise, vous pouvez utiliser des tableaux.
*/

/*
  ETAPE 4 ENV
  -> Si vous prenez la solution liste chainee (trop classe wahou), faites une
	 fonction qui transforme le char **env en t_list *env. Cette fonction
	 ressemblera a l’exo de piscine "my_params_in_list.c" (Jour 11).
	 Afficher cette liste.
  -> Si vous choisissez de garder un tableau, afficher simplement ce tableau.
*/

/*
  ETAPE 5 SETENV
  liste chainee : ajouter un element a la liste. A la fin de la liste. Pas
  tres difficile :) mais attention, vous devez verifier si l’element n’
  existe pas deja et si c’est le cas modifier cet element.
  tableau : ajouter un element a la fin du tableau. Pour ca, il va falloir
  faire un realloc, c’est a dire free(env) (sauf si c’est le tableau de depart)
  malloc(la taille du tableau d’avant + 1). pareil, si l’element existe,
  il faut le modifier.
*/

/*
  ETAPE 6 UNSETENV
  liste chainee : parcourir sa liste, trouver (ou pas) l’element, l’enlever.
  pop_elem_from_list (google :))
  tableau : parcourir le tableau, trouver (ou pas) l’element, realloc le
  tableau en enlevant l’elem.
*/

/*
  ETAPE 7 CD
  la, je me contenterait de vous dire "chdir". Et man. Et google.
*/