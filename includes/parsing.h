/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:34:33 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/07 16:55:59 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../includes/minishell.h"
# include "../includes/builtins.h"
# include "../sources/libft/includes/libft.h"

typedef struct s_ms
{
	int				type;
	struct s_ms		*next;
	char			*str;
}					t_ms;


/*ERRORS*/

/*LEXER*/
int		ft_lexer(t_ms *lex, char *str);

t_ms	*ft_lstnew_ms(void *content, int type);
void	ft_lstadd_back_ms(t_ms **lst, t_ms *new);
void    ft_view_lst(t_ms *lst);
void	ft_lstclear_ms(t_ms *lst);
void	ft_clean_lst(t_ms **lex);

char	*ft_strcat(char *dest, char *src);
char	**ft_split(char const *s, char sep);

int		ft_append(t_ms **lex, char *str);
int		ft_check_quotes(char *str, char c);
int		ft_chevron(t_ms **lex, char *str, char c);

int		char_is_space(char c);
int		char_is_separator(char c);

/*EXEC*/

/*BUILTINS*/

#endif