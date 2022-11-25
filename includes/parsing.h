/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:34:33 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/25 15:14:32 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "builtins.h"
# include "../sources/libft/includes/libft.h"

typedef struct s_lstms
{
	int					type;
	struct s_lstms		*next;
	char				*str;
}					t_lstms;

typedef struct s_parse
{
	char	**tab_cmd;
	char	*file_in;
	char	*delimiter;
	int		fd_in;
	int		fd_out;
	int		type;
	int		if_pipe;
	int		if_heredoc;
}			t_parse;

/*ERRORS*/
# define ERR_CHEVRON "syntax error near unexpected token"

/*LEXER*/

t_lstms	*ft_lstnew_ms(void *content, int type);
void	ft_lstadd_back_ms(t_lstms **lst, t_lstms *new);
void    ft_view_lst(t_lstms *lst);
void	ft_lstclear_ms(t_lstms *lst);
char	*ft_malloc(int len);

int		ft_lstsize_ms(t_lstms *lst);

char	*ft_strcat(char *dest, char *src);
char	**ft_split(char const *s, char sep);

int		ft_append(t_lstms *lex, char *str);
int		ft_check_quotes(char *str, char c);
int		ft_chevron(t_lstms *lex, char *str, char c);

int		char_is_space(char c);
int		char_is_separator(char c);
int		char_is_quote(char *str, char c);

char	*ft_clean_simple_quotes(char *str);
char	*ft_stock_str(char *old_str, char c);

void	ft_print_struc_parse(t_parse *parse, int count);


#endif