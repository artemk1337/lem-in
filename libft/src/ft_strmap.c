/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:10:51 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/05 12:01:30 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*tmp;
	char	*dst;
	char	*dst1;

	if (!s || !f || !(dst = ft_memalloc((size_t)ft_strlen((char *)s) + 1)))
		return (NULL);
	tmp = (char *)s;
	dst1 = dst;
	while (*tmp)
		*(dst1++) = f(*(tmp++));
	return (dst);
}
