/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:50:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/02 10:03:37 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	char  prompt[3] = "$>";
	char  *str;
	t_ms *lex; 
		
	(void)argc;
	(void)argv;
	(void)env;

	lex = NULL;
	while (1)
	{
		str = readline(prompt);
		if (ft_lexer(lex, str) == 0)
		{
			ft_lstclear_ms(lex);
			return (0);
		}
		add_history(str);
		if (str == NULL)
		{
			free (str);
			exit (0);
		}
		free (str);
	}
	return (0);
}