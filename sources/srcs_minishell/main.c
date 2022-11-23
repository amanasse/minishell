/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/23 16:49:56 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals()
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT,SIG_IGN);
}

void	ft_init_all(t_minishell *minishell)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
}

int main(int argc, char **argv, char **env)
{
	char			prompt[4] = "$> ";
	char			*str;
	t_minishell		minishell;
		
	(void)argc;
	(void)argv;
	ft_init_all(&minishell);
	copy_of_env(env, &minishell);
	signals();
	while (1)
	{
		minishell.lstms = NULL;
		str = readline(prompt);
		ft_lexer(&minishell, str);
		minishell.count = ft_clean_lst(&minishell);
		// ft_view_lst(minishell.lstms);
		ft_build_struc_parse(&minishell, minishell.count);
		if (execution(&minishell) == 0)
			return (0);
		if (open("heredoc.txt", O_RDONLY) != -1)
			unlink("heredoc.txt");
		add_history(str);
		if (str == NULL)
		{
			write(1, "exit\n", 5);
			free (str);
			free_parse(&minishell);
			ft_lstclear_ms(minishell.lstms);
			exit (0);
		}
		free_parse(&minishell);
		ft_lstclear_ms(minishell.lstms);
		// ft_lstclear_env(minishell.environ);  uniquement si un return 
		free(str);
	}
	return (0);
}