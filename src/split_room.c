/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:04:40 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/29 13:24:52 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	dop_1_split_room(t_next *neigh, t_next *neigh_neigh,
	t_room *in, t_room *out)
{
	while (neigh)
	{
		if (!neigh->room->was_here)
		{
			if (neigh->room->out)
				neigh_neigh = neigh->room->out->next;
			else
				neigh_neigh = neigh->room->next;
			while (neigh_neigh && neigh_neigh->room != out)
				neigh_neigh = neigh_neigh->next;
			neigh_neigh->room = in;
		}
		neigh = neigh->next;
	}
}

void	dop_2_split_room(t_next *neigh, t_next *neigh_neigh,
	t_room *in, t_room *out)
{
	g_lemin->edge++;
	neigh->weight = -1;
	neigh->toggle = 1;
	neigh->global_toggle = 1;
	neigh->next = NULL;
	neigh->room = out->prev;
	in->next = neigh;
	in->prev = out->prev;
}

void	dop_3_split_room(t_next *neigh,
	t_room *in, t_room *out)
{
	while (neigh)
	{
		if (neigh->room == out->prev)
		{
			neigh->room = in;
			neigh->weight = 0;
		}
		neigh = neigh->next;
	}
}

t_room	*split_room(t_room *curr, t_tmp *list)
{
	t_next	*neigh;
	t_next	*neigh_neigh;
	t_room	*in;
	t_room	*out;

	if (curr->in || curr->out)
		exit(1);
	list = init_tmp(list, 1, curr->name);
	in = find_last_room(list);
	out = curr;
	out->in = in;
	in->out = out;
	neigh = out->next;
	dop_1_split_room(neigh, neigh_neigh, in, out);
	if (!(neigh = ft_memalloc(sizeof(t_next))))
		exit(1);
	dop_2_split_room(neigh, neigh_neigh, in, out);
	neigh = out->next;
	dop_3_split_room(neigh, in, out);
	out->prev = in;
	in->was_here = 1;
	out->was_here = 1;
	return (in->prev);
}
