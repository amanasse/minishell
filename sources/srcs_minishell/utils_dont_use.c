

void	ft_free_tab_cmd(t_parse *parse) // a supprimer
{
	int i;
	int j;

	i = 0;
	while (parse[i].tab_cmd != NULL)
	{
		j = 0;
		while (parse[i].tab_cmd[j] != NULL)
		{
			free(parse[i].tab_cmd[j]);
			j++;
		}
		free(parse[i].tab_cmd);
		i++;
	}
	free (parse);
}



char	*ft_supp_quotes(char *str, int i, int quote, char *new_str)
{
	if (str[i] == '"')
	{
		if (quote == 0)
			quote = 1;
	}
	else if (str[i] == '\'')
	{
		if (quote == 1)
			new_str = ft_stock_str(new_str, str[i]);
	}
	return (new_str);
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
			printf("parse[%d]->type = %d\n", i, parse[i].type);
			// printf("parse[%d]->file_in = %s\n", i, parse[i].file_in);
			// printf("parse[%d]->if_heredoc = %d\n", i, parse[i].if_heredoc);
			j++;
		}
		i++;
	}
}