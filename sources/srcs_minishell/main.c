/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/25 11:13:15 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*g_minishell;

void	replace_prompt()
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

void	signals()
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	ft_init_all(t_minishell *minishell, char **env)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
	g_minishell = minishell;
	copy_of_env(env, minishell);
	signals();
}

void	exit_control_d(char *str, t_minishell *minishell)
{
	write(1, "exit\n", 5);
	free (str);
	free_parse(minishell);
	ft_lstclear_ms(minishell->lstms);
	ft_lstclear_env(minishell->environ); 
	exit (0);
}

int main(int argc, char **argv, char **env)
{
	char			prompt[4] = "$> ";
	char			*str;
	t_minishell		minishell;
		
	(void)argc;
	(void)argv;
	ft_init_all(&minishell, env);
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
		if (str == NULL)
			exit_control_d(str, &minishell);
		free_parse(&minishell);
		ft_lstclear_ms(minishell.lstms);
		free(str);
	}
	return (0);
}