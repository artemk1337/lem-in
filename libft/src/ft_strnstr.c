/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 18:23:35 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/06 21:24:07 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	a;
	size_t	b;

	if (!*s2)
		return ((char *)s1);
	a = 0;
	while (s1[a] != '\0' && a < len)
	{
		if (s1[a] == s2[0])
		{
			b = 1;
			while (s2[b] != '\0' && s1[a + b] == s2[b] && a + b < len)
				b++;
			if (s2[b] == '\0')
				return ((char *)&s1[a]);
		}
		a++;
	}
	return (NULL);
}
