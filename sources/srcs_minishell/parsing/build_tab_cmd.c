/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tab_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:29:36 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/16 15:12:00 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//norminette ok

int	ft_count_cmd(t_lstms *lex)
{
	int count;

	count = 0;
	while (lex != NULL)
	{
		if (lex->type != 2)
			count++;
		lex = lex->next;
	}
	return (count);
}

void	ft_init_struc_parse(t_parse *parse, int i)
{
	parse[i].file_in = NULL;
	parse[i].tab_cmd = NULL;
	parse[i].fd_in = 0;
	parse[i].if_heredoc = 0;
	parse[i].fd_out = 1;
	parse[i].if_pipe = 0;
}

void	ft_fill_parse(t_parse *parse, t_lstms *temp, int j, int i)
{
	parse[j].tab_cmd[i] = temp->str;
	if (temp->type == 3 || temp->type == 4 
		|| temp->type == 5 || temp->type == 6)
		parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
	parse[j].type = temp->type;
	if (temp->next != NULL && temp->next->type == 2)
		parse[j].if_pipe = 1;
}

void	ft_fill_tab_cmd(t_lstms *temp, t_parse *parse)
{
	int		j;
	int		i;
	int		nb_cmd;

	j = 0;
	while (temp != NULL)
	{
		i = 0;
		nb_cmd = ft_count_cmd(temp);
		parse[j].tab_cmd = malloc(sizeof(char *) * (nb_cmd + 1));
		if (parse[j].tab_cmd == NULL)
			return ;
		while (temp->type != 2 && temp != NULL)
		{
			ft_fill_parse(parse, temp, j, i);
			i++;
			temp = temp->next;
			if (temp == NULL)
				break ;
		}
		parse[j].tab_cmd[i] = NULL;
		if (temp != NULL)
			temp = temp->next;
		j++;
	}
	parse[j].tab_cmd = NULL;
}

void	ft_print_struc_parse(t_parse *parse, int k) // a supprimer
{
	int i;
	int	j;

	i = 0;
	while (i < k)
	{
		j = 0;
		while (parse[i].tab_cmd[j] != NULL)
		{
			printf("parse[%d]->tab_cmd[%d] = [%s]\n", i, j, parse[i].tab_cmd[j]);
			// printf("parse[%d]->type = %d\n", i, parse[i].type);
			// printf("parse[%d]->file_in = %s\n", i, parse[i].file_in);
			j++;
		}
		i++;
	}
}

void	ft_build_struc_parse(t_minishell *minishell, int count)
{
	t_lstms	*temp;
	int		i;

	temp = minishell->lstms;
	i = 0;
	minishell->parse = malloc(sizeof(t_parse) * (count + 2));
	if (minishell->parse  == NULL)
		return ;
	while (minishell->parse && i < (count + 2))
	{	
		ft_init_struc_parse(minishell->parse, i);
		i++;
	}
	ft_fill_tab_cmd(temp, minishell->parse);
	// ft_print_struc_parse(minishell->parse, count + 1);
	// free(parse->tab_cmd);
	// free(parse);
}