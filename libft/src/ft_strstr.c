/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:58:01 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/04 18:13:24 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(char *dst, char *src)
{
	int i;
	int k;
	int j;

	i = -1;
	j = 0;
	if (src[0] == '\0')
		return (dst);
	while (dst[++i] != '\0')
	{
		k = 0;
		while (dst[i + k] == src[k])
		{
			if (src[++k] == '\0')
			{
				j = 1;
				break ;
			}
		}
		if (j == 1)
			break ;
	}
	if (j == 1)
		return (dst + i);
	return (0);
}
