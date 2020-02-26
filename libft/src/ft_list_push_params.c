/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 11:56:48 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/09 11:56:56 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_list_push_params(int ac, char **av)
{
	t_list	*mass;
	t_list	*x;
	int		i;

	i = -1;
	x = NULL;
	mass = NULL;
	if (ac > 0)
	{
		while (++i < ac)
		{
			mass = ft_create_elem(av[i]);
			mass->next = x;
			x = mass;
		}
	}
	return (mass);
}
