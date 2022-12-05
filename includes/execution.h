/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:16:02 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/05 16:30:19 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"
# include "builtins.h"

typedef struct s_exec
{
	int				count_pipe;
}					t_exec;

void	close_fd(int *fd);
void	dupper_child(int tmp_fd);

#endif