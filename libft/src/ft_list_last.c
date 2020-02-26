/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 20:06:13 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/08 20:06:34 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_list_last(t_list *begin_list)
{
	t_list *mass;

	if (begin_list)
	{
		mass = begin_list;
		while (mass->next)
			mass = mass->next;
		return (mass);
	}
	else
		return (0);
}
