/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:26:32 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/06 20:53:23 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t a;
	size_t b;
	size_t i;

	a = 0;
	b = 0;
	i = 0;
	while (dst[a] != '\0')
		a++;
	while (src[b] != '\0')
		b++;
	if (size > a)
		b += a;
	else
		b += size;
	while (src[i] != '\0' && a + 1 < size)
	{
		dst[a] = src[i];
		a++;
		i++;
	}
	dst[a] = '\0';
	return (b);
}
