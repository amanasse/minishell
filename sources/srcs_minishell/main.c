/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/07 11:19:08 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*g_minishell;

void	replace_prompt(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	write(2, "\n", 1);
	rl_redisplay();
}

void	signal_handler(int signum, siginfo_t *sa, void *context)
{
	(void)context;
	(void)sa;
	if (signum == SIGINT)
	{
		g_minishell->shell.status = 130;
		if (g_minishell->pid == 0)
			replace_prompt();
		else
		{
			write(2, "", 1);
			rl_redisplay();
		}
	}
}

void	signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_child(void)
{
	struct sigaction	sb;

	sigemptyset(&sb.sa_mask);
	sb.sa_flags = SA_RESTART | SA_SIGINFO;
	signal(SIGQUIT, SIG_DFL);
}

int	main(int argc, char **argv, char **env)
{
	char			prompt[4];
	char			*str;
	t_minishell		minishell;

	(void)argc;
	(void)argv;
	ft_init_all(&minishell, env, prompt);
	signals();
	while (1)
	{
		minishell.pid = 0;
		minishell.lstms = NULL;
		str = readline(prompt);
		ft_lexer(&minishell, str, 0);
		minishell.count = ft_clean_lst(&minishell);
		if (minishell.error == 0)
		{
			ft_build_struc_parse(&minishell, minishell.count);
			if (execution(&minishell) == -1)
				return (0);
		}
		control_d_or_clear(str, &minishell);
	}
	return (0);
}
