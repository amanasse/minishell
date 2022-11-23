/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/23 12:06:34 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_all(t_minishell *minishell)
{
	ft_bzero(minishell, sizeof(t_minishell));
}

void	free_parse(t_minishell *minishell)
{
	int	i;

	minishell->index_cmd = 0;
	while (minishell->parse[minishell->index_cmd].tab_cmd)
	{
		i = 0;
		while (minishell->parse[minishell->index_cmd].tab_cmd[i])
		{
			free(minishell->parse[minishell->index_cmd].tab_cmd[i]);
			i++;
		}
		free(minishell->parse[minishell->index_cmd].tab_cmd);
		minishell->index_cmd++;
	}
	free(minishell->parse);
	minishell->index_cmd = 0;
	// free(minishell->tab_env);
}

int	execution(t_minishell *minishell)
{
	int	tmp_pipefd;
	int	pipefd[2];
	int	i;

	tmp_pipefd = 0;
	minishell->index_cmd = 0;
	while (minishell->parse[minishell->index_cmd].tab_cmd)
	{
		if (pipe(pipefd) == -1)
			return (0);
		env_in_tab(minishell);
		if (minishell->tab_env == NULL)
			return (0);
		ft_fork(minishell, pipefd, tmp_pipefd);
		free(minishell->tab_env);
		minishell->tab_env = NULL;
		close(pipefd[1]);
		if (tmp_pipefd > 0)
			close (tmp_pipefd);
		tmp_pipefd = pipefd[0];
		minishell->index_cmd++;
	}
	if (tmp_pipefd > 0)
		close (tmp_pipefd);
	i = 0;
	while (i < minishell->count + 1)
	{	
		wait(NULL);
		i++;
	}
	return (1);
}

int main(int argc, char **argv, char **env)
{
	char			prompt[3] = "$>";
	char			*str;
	t_minishell		minishell;
		
	(void)argc;
	(void)argv;
	ft_init_all(&minishell);
	copy_of_env(env, &minishell);

	while (1)
	{
		minishell.lstms = NULL;
		str = readline(prompt);
		ft_lexer(&minishell, str);
		minishell.count = ft_clean_lst(&minishell);
		// ft_view_lst(minishell.lstms);
		// printf("minishell.count = %d\n", minishell.count);
		ft_build_struc_parse(&minishell, minishell.count);
		if (execution(&minishell) == 0)
			return (0);
		add_history(str);
		if (str == NULL)
		{
			free (str);
			exit (0);
		}
		free_parse(&minishell);
		ft_lstclear_ms(minishell.lstms);
		// ft_lstclear_env(minishell.environ);  uniquement si un return 
		free(str);
		// return (0);
	}
	return (0);
}