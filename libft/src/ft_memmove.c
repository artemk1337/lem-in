/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:05:20 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/07 22:22:47 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*tmpdst;
	const unsigned char	*tmpsrc;

	i = 0;
	if (!len || dst == src)
		return (dst);
	tmpdst = (unsigned char *)dst;
	tmpsrc = (unsigned char *)src;
	if (tmpsrc < tmpdst)
		while (++i <= len)
			tmpdst[len - i] = tmpsrc[len - i];
	else
		while (len--)
			*(tmpdst++) = *(tmpsrc++);
	return (dst);
}
