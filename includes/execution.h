/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:16:02 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/16 10:51:21 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../includes/minishell.h"
# include "../includes/parsing.h"
# include "../includes/builtins.h"

char	*get_path(t_env *environ, t_parse *parse);


#endif