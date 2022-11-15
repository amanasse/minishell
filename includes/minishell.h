/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:34:33 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/15 17:00:03 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/parsing.h"
# include "../includes/builtins.h"
# include "../includes/execution.h"
# include "../sources/libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_minishell
{
	t_shell		*shell;
	t_lstms		*lstms;
	t_parse		*parse;
}				t_minishell;

int		ft_lexer(t_minishell *minishell, char *str);
void	ft_build_struc_parse(t_minishell *minishell, int count);
int		ft_clean_lst(t_minishell *minishell);


#endif
