/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:26:54 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/26 15:37:24 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			clean_tmp(t_tmp **tmp)
{
	t_tmp	*temp_ptr;

	while (*tmp)
	{
		temp_ptr = (*tmp)->next;
		free(*tmp);
		*tmp = temp_ptr;
	}
}

void			reset_minw_prev(t_tmp *list)
{
	t_tmp *tmp;

	tmp = list;
	while (tmp)
	{
		tmp->room->prev = NULL;
		if (tmp->room != g_lemin->start)
			tmp->room->min_w = INT_MAX / 2;
		tmp->room->was_here = 0;
		tmp->room->ant = 0;
		tmp->room->number_ant = 0;
		tmp = tmp->next;
	}
}
