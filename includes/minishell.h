/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:34:33 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/07 16:56:12 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../includes/builtins.h"
# include "../includes/parsing.h"
# include "../sources/libft/includes/libft.h"


typedef struct s_shell
{
	t_env	        *environ;
	char			**cmd;
    char            *pwd;
    char            *old_pwd;
}					t_shell;

/*ERRORS*/

/*LEXER*/

/*EXEC*/

/*BUILTINS*/

#endif