/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:34:04 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 14:33:44 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	my_check_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	my_contword(char *str, char c)
{
	int	i;
	int	word;
	int	indic;

	i = 0;
	indic = 1;
	word = 0;
	while (str[i])
	{
		if (my_check_sep(str[i], c) == 1)
			indic = 1;
		if (my_check_sep(str[i], c) == 0 && indic == 1)
		{
			word++;
			indic = 0;
		}
		i++;
	}
	return (word);
}

static char	*my_new_word(char *str, int i, int w)
{
	char	*tmp;
	int		j;
	int		size;

	size = i - w;
	j = 0;
	tmp = malloc(sizeof(char) * (w + 1));
	if (tmp == NULL)
		return (NULL);
	while (j < w)
	{
		tmp[j] = str[size];
		size++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

static char	**my_make_tab(char *str, char c, char **tab, int m)
{
	int	i;
	int	j;
	int	w;
	int	indic;

	indic = 0;
	w = 0;
	i = -1;
	j = -1;
	while (++i < m)
	{
		while (str[i] && my_check_sep(str[i], c) == 0 && ++w)
		{
			indic = 1;
			i++;
		}
		if (indic == 1)
		{
			tab[++j] = my_new_word(str, i, w);
			indic = 0;
			w = 0;
		}
	}
	tab[++j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	tab = malloc(sizeof(char *) * (my_contword((char *)s, c) + 1));
	if (tab == NULL)
		return (NULL);
	tab = my_make_tab((char *)s, c, tab, i);
	return (tab);
}

/*
int main()
{
	char str1[] = "lorem ipsum dolor sit amet, consectetur adipiscing elit. 
	Sed non risus. Suspendisse";
	char c = ' ';
    char **tab;
	int i;
	
	
	i = 0;
    tab = ft_split(str1, c);
    while (tab[i])
    {
        printf("tab[%d] = [%s]\n", i, tab[i]);
        i++;
    }
    return (0);
}
*/