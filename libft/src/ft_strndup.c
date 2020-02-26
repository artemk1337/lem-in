/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:45:53 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/12 18:45:54 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	int		length;
	int		i;
	char	*temp;

	i = 0;
	if (ft_strlen(s1) >= n)
		length = n;
	else
		length = ft_strlen(s1);
	temp = (char*)malloc(sizeof(char) * (length + 1));
	if (!temp)
		return (0);
	while (s1[i] != '\0' && n > 0)
	{
		temp[i] = s1[i];
		i++;
		n--;
	}
	temp[i] = '\0';
	return (temp);
}
