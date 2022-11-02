/*
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
*/

/* ************************************************************************** 
****************************ENVIRONNEMENT************************************
getenv pour avoir acces a une variable de l'environnement
char *getenv(const char *nom_de_la_variable);
ex : getenv("HOME");
env = tableaux a 2 dim : lignes qui correspondent aux variables et string 
qui correspondent aux valeurs
************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int ac, char **av, char **env)
{
	char	**current_env;
	
	current_env = env;
	while (*current_env)
	{
		printf("%s\n", *current_env);
		current_env++;
	}
}

/* ************************************************************************** 
*******************************FORK&PIPE*************************************
fd 0 = entree standard // stdin
fd 1 = sortie standard // stdout
fd 2 = sortie d'erreur // stderr

int dup2(int oldfd, int newfd);
transforme newfd en une copie de oldfd, fermant auparavant newfd si besoin 
*  Si oldfd n’est pas un descripteur de fichier valable, alors l’appel
échoue et newfd n’est pas fermé.
*  Si oldfd est un descripteur de fichier valable et newfd  a  la  même
valeur que oldfd, alors dup2() ne fait rien et renvoie newfd.

int pipe(int pipefd[2]); // pipefd[0] = lecture  // pipefd[1] = ecriture
crée un tube, un canal unidirectionnel de données qui peut être utilisé pour
la communication entre processus. Le tableau pipefd est utilisé pour renvoyé
2 descripteurs de fichier faisant référence aux extrémités du tube.
Les données écrites sur l'extrémité d'écriture (pipefd[1]) du tube sont mises en
mémoire tampon par le noyau jusqu'à ce qu'elles soient lues sur pipefd[0]
************************************************************************** */
Ex 2 processes : int pipefd[2];
int id = fork();
if (pipe(pipefd) == -1)
	return (1);
if (id == -1)
	return (1);
if (id == 0) //on est dans le process enfant, execute en parallele du parent
//pour communiquer entre les 2 process, on utilise les pipes
{
	close(pipefd[1]); //ferme l'ecriture
	dup2(pipefd[0], STDIN_FILENO); //l'entree du pipe = la sortie du processus
	close(pipefd[0]); //ferme la lecture
}
else //on est dans le process parent
{
	close(pipefd[0]); //ferme la lecture
	dup2(pipefd[1], STDOUT_FILENO); //la sortie du pipe = l'entree du processus
	close(pipefd[1]); //ferme l'ecriture
}

/*************************************************************************** 
**********************************EXECVE*************************************
int execve(const char *path, char *const argv[], char *const envp[]);
ex : execve("/bin/ls", av, env);
************************************************************************** */


int main (int ac, char **av)
{
	__pid_t pid;
	
	pid = fork();
	if (pid == -1)
		return (1);
	if  (pid > 0)
	{
		wait(NULL);
		printf("je suis le pere\n");
	}
	else
	{
		execve("/bin/ls", av, NULL);
		printf("je suis le fils\n");
	}
