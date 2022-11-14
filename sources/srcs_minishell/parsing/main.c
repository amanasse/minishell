/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/14 17:13:54 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"
#include "../../../includes/parsing.h"


int main(int argc, char **argv, char **env)
{
	char  prompt[3] = "$>";
	char  *str;
	t_ms *lex;
	t_shell shell;
		
	(void)argc;
	(void)argv;
	(void)env;

	shell.environ = NULL;
	copy_of_env(env, &shell);
	lex = NULL;
	while (1)
	{
		str = readline(prompt);
		ft_lexer(lex, str, &shell);
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