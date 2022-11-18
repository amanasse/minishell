/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/18 16:33:04 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_all(t_minishell *minishell)
{
	// t_parse		parse;
	// t_env		*environ;
	// t_shell		shell;
	// t_exec		exec;
	
	ft_bzero(minishell, sizeof(t_minishell));
	// environ = NULL;
	// ft_memset(&shell, 0, sizeof(t_shell));
	// ft_memset(&parse, 0, sizeof(t_parse));
	// ft_memset(&exec, 0, sizeof(t_exec));
	
	// minishell->parse = &parse;
	// minishell->environ = environ;
	// //minishell->exec = exec;
	
	// minishell->shell = &shell;
	// minishell->shell->i = 0;
	// minishell->shell->j = 0;
	// minishell->shell->pwd = NULL;
	// minishell->shell->status = 0;
	// minishell->shell->old_pwd = NULL;

}

// void	ft_init_parsing(t_minishell *minishell)
// {
	
// 	//minishell->lstms = NULL;
// }

int main(int argc, char **argv, char **env)
{
	char		prompt[3] = "$>";
	char		*str;
	int			i;
	t_minishell	minishell;
	int			pipefd[2];
	int			tmp_pipefd;

	int			var;
		
	(void)argc;
	(void)argv;
	ft_init_all(&minishell);

	// if (pipe(pipefd2) == -1)
	// 	return (0);
	copy_of_env(env, &minishell);
	while (1)
	{
		minishell.index_cmd = 0;
		str = readline(prompt);
		ft_lexer(&minishell, str);
		// ft_view_lst(minishell.lstms);
		var = 1;
		
		tmp_pipefd = 0;
		
		minishell.count = ft_clean_lst(&minishell);
		ft_build_struc_parse(&minishell, minishell.count);
		while (minishell.parse[minishell.index_cmd].tab_cmd)
		{
			if (pipe(pipefd) == -1)
				return (0);
			printf ("minishell.parse[%d].tab_cmd[0] = %s\n", minishell.index_cmd, minishell.parse[minishell.index_cmd].tab_cmd[0]);
			printf ("minishell.parse[%d].tab_cmd[1] = %s\n", minishell.index_cmd, minishell.parse[minishell.index_cmd].tab_cmd[1]);
			ft_fork1(&minishell, pipefd, tmp_pipefd, minishell.parse[minishell.index_cmd].tab_cmd);
			// close(pipefd[0]);
			close(pipefd[1]);
			if (tmp_pipefd > 0)
				close (tmp_pipefd);
			tmp_pipefd = pipefd[0];
			minishell.index_cmd++;
		}
		if (tmp_pipefd > 0)
				close (tmp_pipefd);
		i = 0;
		while (i < minishell.count + 1)
		{	
			wait(NULL);
			i++;
		}
		// ft_lstclear_ms(minishell.lstms);
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