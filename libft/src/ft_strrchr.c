/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:27:34 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/06 21:13:40 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = (0);
	while (*s)
	{
		if (*s == c)
			tmp = (char *)s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	if (tmp)
		return (tmp);
	return (0);
}
