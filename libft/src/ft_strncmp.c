/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 18:49:44 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/06 21:39:07 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t str;

	str = 0;
	if (n == 0)
		return (0);
	while (s1[str] != '\0' && s2[str] != '\0' && str < n - 1)
	{
		if (s1[str] != s2[str])
			return ((unsigned char)s1[str] - (unsigned char)s2[str]);
		str++;
	}
	return ((unsigned char)s1[str] - (unsigned char)s2[str]);
}
