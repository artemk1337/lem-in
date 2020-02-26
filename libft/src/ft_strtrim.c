/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:28:25 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/08 13:01:09 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

static char	*ft_create_nothing(char *s, char *s1)
{
	int i;

	if (!(s1 = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = -1;
	while (s[++i])
		s1[i] = s[i];
	s1[i] = '\0';
	return (s1);
}

static char	*ft_create_small(char *s, char *s1, int i)
{
	if (!(s1 = (char *)malloc(sizeof(char) * 2)))
		return (NULL);
	s1[0] = s[i];
	s1[1] = '\0';
	return (s1);
}

static char	*ft_create_big(char *s, char *s1, int i, int j)
{
	int k;

	if (!(s1 = (char *)malloc(sizeof(char) * (j - i + 2))))
		return (NULL);
	k = -1;
	while (i <= j)
		s1[++k] = s[++i - 1];
	s1[k + 1] = '\0';
	return (s1);
}

static char	*ft_create_empty(char *s1)
{
	if (!(s1 = (char *)malloc(sizeof(char) * 1)))
		return (NULL);
	s1[0] = '\0';
	return (s1);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*s1;

	s1 = (NULL);
	j = 0;
	i = 0;
	if (!s || !*s)
		return ((char *)s);
	while (s[j])
		j++;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (i == j)
		return (ft_create_empty(s1));
	j--;
	if (i == 0 && s[j + 1] == '\0'
			&& s[j] != ' ' && s[j] != '\n' && s[j] != '\t')
		return (ft_create_nothing((char *)s, s1));
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j--;
	if (i == j)
		return (ft_create_small((char *)s, s1, i));
	else
		return (ft_create_big((char *)s, s1, i, j));
}
