/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/25 15:40:30 by mede-sou         ###   ########.fr       */
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
	if (signum == SIGQUIT)
	{
		g_minishell->shell.status = 131;
		if (g_minishell->pid == 0)
			signal(SIGQUIT, SIG_IGN);
		else
		{
			printf("Quit (core dumped)\n");
			signal(SIGQUIT, SIG_IGN);
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
	sigaction(SIGQUIT, &sa, NULL);
}

void	ft_init_all(t_minishell *minishell, char **env, char *prompt)
{
	prompt[0] = '$';
	prompt[1] = '>';
	prompt[2] = ' ';
	prompt[3] = '\0';
	ft_memset(minishell, 0, sizeof(t_minishell));
	g_minishell = minishell;
	copy_of_env(env, minishell);
	signals();
}

int	main(int argc, char **argv, char **env)
{
	char			prompt[4];
	char			*str;
	t_minishell		minishell;

	(void)argc;
	(void)argv;
	ft_init_all(&minishell, env, prompt);
	while (1)
	{
		minishell.pid = 0;
		minishell.lstms = NULL;
		str = readline(prompt);
		ft_lexer(&minishell, str);
		minishell.count = ft_clean_lst(&minishell);
		ft_build_struc_parse(&minishell, minishell.count);
		if (execution(&minishell) == -1)
			return (0);
		if (open("heredoc.txt", O_RDONLY) != -1)
			unlink("heredoc.txt");
		add_history(str);
		control_d_or_clear(str, &minishell);
	}
	return (0);
}
