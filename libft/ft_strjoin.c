/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 00:59:03 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/12 10:56:33 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	return (i + j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	if (!(s1) || !(s2))
		return (NULL);
	p = malloc (length(s1, s2) + 1);
	if (p == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = ((char *)s1)[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		p[i] = ((char *)s2)[j];
		j++;
		i++;
	}
	p[i] = '\0';
	// free(s1);
	return (p);
}

/*int main()
{
	char s1 [] = "hello ";
	char s2 [] = "1337!";
	printf("%s\n", ft_strjoin(s1,s2));
}*/