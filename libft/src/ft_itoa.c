/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:19:12 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/08 13:01:46 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_count_itoa(char *tmp, int n, int i)
{
	if (n == 0)
		tmp[0] = '0';
	if (n == -2147483648)
	{
		tmp[0] = '-';
		tmp[1] = '2';
		n = 147483648;
	}
	else if (n < 0)
	{
		tmp[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		tmp[i--] = n % 10 + 48;
		n = n / 10;
	}
}

char		*ft_itoa(int n)
{
	char	*tmp;
	int		i;
	int		div;

	div = n;
	i = 0;
	if (n == 0)
		i++;
	while (div != 0)
	{
		div = div / 10;
		i++;
	}
	if (n < 0)
		i++;
	if (!(tmp = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	tmp[i--] = '\0';
	ft_count_itoa(tmp, n, i);
	return (tmp);
}
