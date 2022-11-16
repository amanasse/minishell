/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/16 17:43:42 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_all(t_minishell *minishell)
{
	t_parse		parse;
	t_env		*environ;
	t_shell		shell;
	
	environ = NULL;
	ft_memset(&shell, 0, sizeof(t_shell));
	ft_memset(&parse, 0, sizeof(t_parse));
	minishell->parse = &parse;
	minishell->environ = environ;
	minishell->shell = &shell;
}

void	ft_init_parsing(t_minishell *minishell)
{
	minishell->lstms = NULL;
}

int main(int argc, char **argv, char **env)
{
	char		prompt[3] = "$>";
	char		*str;
	int			i;
	t_minishell	minishell;
	int			count;
	// int		*pipefd;
		
	(void)argc;
	(void)argv;
	(void)env;

	// pipefd = malloc(sizeof(int) * 2);
	// if (pipefd == NULL)
	// 	return (0);
	ft_init_all(&minishell);
	copy_of_env(env, &minishell);
	while (1)
	{
		i = 0;
		ft_init_parsing(&minishell);
		str = readline(prompt);
		ft_lexer(&minishell, str);
		// ft_view_lst(minishell.lstms);
		count = ft_clean_lst(&minishell);
		// ft_view_lst(minishell.lstms);
		ft_build_struc_parse(&minishell, count);
		// if (pipe(pipefd) == -1)
		// 	return (0);
		// ft_fork1(&minishell, pipefd);
		// ft_fork2(&minishell, pipefd);
		// close(pipefd[1]);
		// close(pipefd[0]);
		// wait(NULL);
		// wait(NULL);
		while (minishell.parse[i].tab_cmd)
		{
			builtins(minishell.parse[i].tab_cmd, &minishell);
			i++;
		}
		ft_lstclear_ms(minishell.lstms);
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