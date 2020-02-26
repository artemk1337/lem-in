/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:45:25 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/06 20:42:09 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	if (n == 0)
		return (0);
	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	i = 0;
	while (tmps1[i] == tmps2[i] && i < n - 1)
		i++;
	return ((int)(tmps1[i] - tmps2[i]));
}
