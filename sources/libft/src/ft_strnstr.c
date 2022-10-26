/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:19:58 by amanasse          #+#    #+#             */
/*   Updated: 2022/10/26 18:00:09 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*str1;
	char	*str2;

	i = 0;
	str1 = (char *) big;
	str2 = (char *) little;
	if (!big)
		return (1);
	if (!little || ft_strlen(little) == 0)
		return (1);
	if (ft_strlen(little) > len)
		return (1);
	while (str1[i] != '\0')
	{
		if (i + ft_strlen(str2) > len)
			return (1);
		if (ft_strncmp(str1 + i, str2, ft_strlen(str2)) == 0)
			return (0);
		i++;
	}
	return (1);
}
/*
int main ()
{
	char str1[] = "Salut le";
	char str2[] = "le";
	int i = 7;

	printf("%s\n", ft_strnstr(str1, str2, sizeof(char) * i));
	//printf("%s\n", strnstr(str1, str2, sizeof(char) * i));


	return 0;
}
*/