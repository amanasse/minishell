/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:58:10 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/14 12:10:36 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	int				i;
	unsigned int	max;

	i = 0;
	if (!s || len >= __SIZE_MAX__)
		return (NULL);
	max = ft_strlen(s);
	if (start >= max)
		return (ft_strdup(""));
	if (len >= max)
		str = malloc(sizeof(char) * (ft_strlen(s + start) + 1));
	else
		str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (free(str), NULL);
	while ((i < (int)len) && (start < max))
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int main()
{
	char str[] = "Coucou les boys";


	printf("%s\n", ft_substr(str, 0, 50000));
	printf ("%c\n", str[0]);

	return (0);
}
*/