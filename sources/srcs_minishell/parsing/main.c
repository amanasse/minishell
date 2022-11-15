/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/15 12:26:29 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	char	prompt[3] = "$>";
	char	*str;
	char	**cmd;
	t_ms	*lex;
	t_parse	*parse;
	t_shell	shell;
	int		*pipefd;
		
	(void)argc;
	(void)argv;

	shell.environ = NULL;
	parse = NULL;
	lex = NULL;
	pipefd = malloc(sizeof(int) * 2);
	if (pipefd == NULL)
		return (0);
	copy_of_env(env, &shell);
	while (1)
	{
		str = readline(prompt);
		ft_lexer(lex, str, &shell);
		if (pipe(pipefd) == -1)
			return (0);
		cmd = parse[0].tab_cmd;
		ft_fork1(&shell, cmd, pipefd, parse);
		cmd = parse[1].tab_cmd;
		ft_fork2(&shell, cmd, pipefd, parse);
		close(pipefd[1]);
		close(pipefd[0]);
		wait(NULL);
		wait(NULL);
		add_history(str);
		if (str == NULL)
		{
			free (str);
			exit (0);
		}
		free (str);
	}
	// ft_lstclear_env(shell.environ);
	return (0);
}