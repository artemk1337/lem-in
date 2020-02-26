/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:50:04 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/10 16:38:40 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static int	ft_count_words(char *s, char c)
{
	int i;
	int tr;
	int words;

	tr = 0;
	i = 0;
	words = 0;
	while (s[i])
	{
		if (tr == 0 && s[i] != c)
		{
			words++;
			tr = 1;
		}
		else if (tr == 1 && s[i] == c)
			tr = 0;
		i++;
	}
	return (words + 1);
}

static void	ft_put(char **tmp, char *s, char c)
{
	int i;
	int j;
	int tr;
	int words;

	tr = 0;
	words = -1;
	i = -1;
	while (s[++i])
	{
		if (tr == 0 && s[i] != c && !(j = 0) && (words++ || 1))
			tr = 1;
		else if (tr == 1 && s[i] == c)
		{
			tmp[words][j] = '\0';
			tr = 0;
		}
		if (tr == 1)
			tmp[words][j] = s[i];
		j++;
	}
	if (tr == 1 && s[i] == '\0')
		tmp[words][j] = '\0';
}

static int	ft_clean(char **tmp, int i)
{
	while (i >= 0)
		free(tmp[i--]);
	free(tmp);
	return (0);
}

static int	ft_create_mass_for_symb(char *s, char c, char **tmp)
{
	int i;
	int tr;
	int words;
	int symb;

	tr = 0;
	i = -1;
	words = 0;
	while (s[++i])
	{
		if (tr == 0 && s[i] != c && (symb = 1) && (words++ || 1))
			tr = 1;
		else if (tr == 1 && s[i] == c)
		{
			if (!(tmp[words - 1] = (char *)malloc(sizeof(char) * symb)))
				return (ft_clean(tmp, words - 1));
			tr = 0;
		}
		symb++;
	}
	if (tr == 1 && s[i] == '\0')
		if (!(tmp[words - 1] = (char *)malloc(sizeof(char) * symb)))
			return (ft_clean(tmp, words - 1));
	tmp[words] = (NULL);
	return (1);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (NULL);
	if (!s)
		return (NULL);
	while (s[i] == c)
		i++;
	i = 0;
	if (!(tmp = (char**)malloc(sizeof(*tmp) * ft_count_words((char*)s, c))))
		return (0);
	if (!(ft_create_mass_for_symb((char *)s, c, tmp)))
		return (NULL);
	ft_put(tmp, (char *)s, c);
	return (tmp);
}
