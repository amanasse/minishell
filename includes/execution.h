/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:16:02 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/15 12:23:09 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../includes/minishell.h"
# include "../includes/parsing.h"
# include "../includes/builtins.h"

int		ft_fork1(t_shell *shell, char **cmd, int *pipefd, t_parse *parse);
int		ft_fork2(t_shell *shell,char **cmd, int *pipefd, t_parse *parse);
char	*get_path(t_shell *shell, t_parse *parse);


#endif