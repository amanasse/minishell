/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:21:36 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/02 15:22:14 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <sys/types.h>
# include <dirent.h>


/*BUILTINS*/

char	*cmd_cd(char **cmd);
int		cmd_exit(char **cmd);
void	cmd_pwd(char **cmd);

/*UTILS*/
int		ft_strcmp(char *s1, char *s2);


#endif