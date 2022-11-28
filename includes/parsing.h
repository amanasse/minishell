/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:34:33 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/28 14:59:54 by mede-sou         ###   ########.fr       */
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
# define ERR_SYNTAX "minishell: syntax error near unexpected token 'newline'"
# define ERR_SY_TOK "minishell: syntax error near unexpected token"

t_lstms	*ft_lstnew_ms(void *content, int type);
void	ft_lstadd_back_ms(t_lstms **lst, t_lstms *new);
void	ft_view_lst(t_lstms *lst);
void	ft_lstclear_ms(t_lstms *lst);
char	*ft_malloc(int len);
int		ft_lstsize_ms(t_lstms *lst);

char	*ft_strcat(char *dest, char *src);
char	**ft_split(char const *s, char sep);
char	*ft_stock_str(char *old_str, char c);

int		ft_check_quotes(char *str, char c);

int		char_is_space(char c);
int		char_is_separator(char c);
int		char_is_quote(char *str, char c);
int		while_char_is_caract(char *str, int i);
int		check_if_quotes_are_closed(char *str, int i);

int		ft_count_cmd(t_lstms *lex);
void	ft_print_struc_parse(t_parse *parse, int count);
void	ft_init_struc_parse(t_parse *parse, int i);

#endif