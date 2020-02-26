/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 20:04:02 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/08 20:04:17 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list *new_el;

	if (*begin_list)
	{
		new_el = ft_create_elem(data);
		new_el->next = *begin_list;
		*begin_list = new_el;
	}
	else
		*begin_list = ft_create_elem(data);
}
