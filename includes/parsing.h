/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:34:33 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/08 14:59:19 by mede-sou         ###   ########.fr       */
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

typedef struct s_parse
{
	char	**tab_cmd;
	char	*file_in;
	int		fd_in;
	int		fd_out;
	int		type;
	int		if_pipe;
	int		if_heredoc;
}			t_parse;

/*ERRORS*/

/*LEXER*/
int		ft_lexer(t_ms *lex, char *str);

t_ms	*ft_lstnew_ms(void *content, int type);
void	ft_lstadd_back_ms(t_ms **lst, t_ms *new);
void    ft_view_lst(t_ms *lst);
void	ft_lstclear_ms(t_ms *lst);
void	ft_clean_lst(t_ms **lex);
int		ft_lstsize_ms(t_ms *lst);

char	*ft_strcat(char *dest, char *src);
char	**ft_split(char const *s, char sep);

int		ft_append(t_ms **lex, char *str);
int		ft_check_quotes(char *str, char c);
int		ft_chevron(t_ms **lex, char *str, char c);

int		char_is_space(char c);
int		char_is_separator(char c);

void	ft_build_struc_parse(t_ms **lex, int count);


/*EXEC*/

/*BUILTINS*/

#endif