/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:35:47 by amanasse          #+#    #+#             */
/*   Updated: 2022/09/07 16:41:00 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*stock_save(char *dest, char *exline, char *exsave)
{
	int		i;
	char	*save;
	int		j;

	j = ft_strlen_gnl(exsave) - ft_strlen_gnl(exline);
	save = malloc(sizeof(char) * (j + 1));
	if (save == NULL)
		return (NULL);
	i = 0;
	while (j > 0)
	{
		save[i] = dest[i];
		i++;
		j--;
	}
	save[i] = '\0';
	return (save);
}

char	*stock_line(char *dest, int octet)
{
	int		i;
	char	*line;

	i = 0;
	while (dest[i] != '\0')
	{
		if (dest[i] == '\n')
			break ;
		i++;
	}
	line = malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (dest[i] != '\0' && octet > 0)
	{
		line[i] = dest[i];
		if (dest[i] == '\n')
			break ;
		i++;
		octet--;
	}
	line[i + 1] = '\0';
	return (line);
}

int	ft_join(char *dest, char **save, int fd)
{
	char	*tmp;
	int		nb_octet;

	nb_octet = 1;
	while (check_sep(*save) == 0 && nb_octet != 0)
	{	
		nb_octet = read(fd, dest, BUFFER_SIZE);
		dest[nb_octet] = '\0';
		if (*save && dest && dest[0] == '\0' && *save[0] == '\0')
			return (0);
		if (*save && dest && nb_octet > 0)
		{
			tmp = *save;
			*save = ft_strjoin_gnl(*save, dest);
			if (!*save)
			{
				free (tmp);
				return (0);
			}
			free(tmp);
			tmp = NULL;
		}
	}
	return (1);
}

char	*free_stock_save(char **save, char **line)
{
	char	*tmp;

	tmp = *save;
	*save = stock_save(*save + ft_strlen_gnl(*line), *line, *save);
	free(tmp);
	tmp = NULL;
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	dest[BUFFER_SIZE];
	static char	*save;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, dest, 0) < 0)
		return (NULL);
	if (save == NULL)
	{
		save = ft_strdup_gnl("");
		if (!save)
			return (NULL);
	}
	if (ft_join(dest, &save, fd) == 0)
	{
		if (save && save[0] == '\0')
			return (free(save), save = NULL, NULL);
	}
	if (save && check_sep(save) == 1)
	{
		line = stock_line(save, ft_strlen_gnl(save));
		return (free_stock_save(&save, &line));
	}
	return (line = stock_line_last(save), free_stock_save(&save, &line));
}
