/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 20:05:21 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/08 20:05:34 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_list_size(t_list *begin_list)
{
	t_list	*mass;
	int		i;

	i = 0;
	if (begin_list)
	{
		mass = begin_list;
		while (mass)
		{
			mass = mass->next;
			i++;
		}
		return (i);
	}
	else
		return (0);
}
