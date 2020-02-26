/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 20:00:17 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/09 11:45:45 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_list_push_back_a(t_list *list, void *data)
{
	if (list->next == 0)
		list->next = ft_create_elem(data);
	else
		ft_list_push_back_a(list->next, data);
}

void		ft_list_push_back(t_list **begin_list, void *data)
{
	if (!*begin_list)
		*begin_list = ft_create_elem(data);
	else
		ft_list_push_back_a(*begin_list, data);
}
