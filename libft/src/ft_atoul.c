/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:08:56 by aolen             #+#    #+#             */
/*   Updated: 2020/02/18 14:08:56 by aolen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_atoul(const char *str)
{
	int				i;
	unsigned long	numbers;

	i = 0;
	numbers = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' && ((str[i + 1] - '0' < 10)
							   && (str[i + 1] - '0' >= 0)))
		i++;
	while ((str[i] - '0' < 10) && (str[i] - '0' >= 0))
	{
		numbers = numbers * 10 + (str[i++] - '0');
	}
	return (numbers);
}