/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solutions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:25:38 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/26 16:11:21 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/* <===============================> */
/* <========== Суурбалле ==========> */
/* <============ Готово ===========> */


int		suurballe(t_tmp *list)
{
	t_room	*curr;
	t_room	*prev;
	t_next	*neigh;
	t_next	*neigh_neigh;
	int		len_way;

	curr = g_lemin->finish;
	prev = curr->prev;
	len_way = count_len_way();
	if (len_way == -1)
		return (0);
	while (prev)
	{
		neigh = curr->next;
		while (neigh && neigh->room != prev)
			neigh = neigh->next;
		neigh->weight = -1;
		neigh_neigh = neigh->room->next;
		while (neigh_neigh && neigh_neigh->room != curr)
			neigh_neigh = neigh_neigh->next;
		neigh_neigh->toggle = 0;
		if (curr == g_lemin->start)
			break ;
		if (curr != g_lemin->finish)
			prev = split_room(curr, list);
		curr = prev;
		prev = curr->prev;
	}
	return (len_way);
}

