/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tab_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:29:36 by mede-sou          #+#    #+#             */
/*   Updated: 2022/11/08 17:34:51 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"
#include "../../../includes/minishell.h"

void	ft_print_struc_parse(t_parse *parse, int k)
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
			printf("parse[%d]->type = %d\n", i, parse[i].type);
			printf("parse[%d]->file_in = %s\n", i, parse[i].file_in);
			j++;
		}
		i++;
	}
}

int	ft_count_cmd(t_ms *lex)
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

void	ft_build_struc_parse(t_ms **lex, int count)
{
	t_ms	*temp;
	t_parse	*parse;
	int		i;
	int		j;
	int		nb_cmd;

	temp = *lex;
	nb_cmd = 0;
	i = 0;
	parse = malloc(sizeof(t_parse) * (count + 2));
	if (parse == NULL)
		return ;
	while (parse && i < (count + 2))
	{	
		ft_init_struc_parse(parse, i);
		i++;
	}
	j = 0;
	while (temp != NULL)
	{
		i = 0;
		nb_cmd = ft_count_cmd(temp);
		parse[j].tab_cmd = malloc(sizeof(char *) * (nb_cmd + 1));
		while (temp->type != 2 && temp != NULL)
		{
			if (temp->type == 3 || temp->type == 4 || temp->type == 5 || temp->type == 6)
				parse[j].file_in = ft_strncpy(temp->str, ft_strlen(temp->str));
			parse[j].tab_cmd[i] = temp->str;
			parse[j].type = temp->type;
			i++;
			if (temp->next != NULL && temp->next->type == 2)
				parse[j].if_pipe = 1;
			temp = temp->next;
			if (temp == NULL)
				break ;
		}
		parse[j].tab_cmd[i] = NULL;
		j++;
		if (temp != NULL)
			temp = temp->next;
	}
	parse[j].tab_cmd = NULL;
	ft_print_struc_parse(parse, j);
}