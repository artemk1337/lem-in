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

void	dop_end(t_tmp *list)
{
	t_tmp	*curr;
	t_next	*neigh;

	curr = list;
	while (curr)
	{
		neigh = curr->room->next;
		while (neigh)
		{
			neigh->toggle = 1;
			neigh->weight = 1;
			neigh = neigh->next;
		}
		curr->room->out = NULL;
		curr->room->in = NULL;
		curr = curr->next;
	}
}

void	free_(t_tmp *curr)
{
	free(curr->room->next);
	free(curr->room->name);
	free(curr->room);
	free(curr);
}

void	dop_1(t_room *out, t_tmp *curr)
{
	t_next	*neigh_neigh;
	t_next	*neigh;

	neigh = out->next;
	while (neigh)
	{
		if (neigh->room->out)
			neigh_neigh = neigh->room->out->next;
		else
			neigh_neigh = neigh->room->next;
		while (neigh_neigh && neigh_neigh->room != curr->room)
			neigh_neigh = neigh_neigh->next;
		if (neigh_neigh)
			neigh_neigh->room = out;
		neigh = neigh->next;
	}
}

t_tmp	*dop_2(t_tmp *next, t_tmp *curr)
{
	next = curr->next;
	curr->next = NULL;
	curr = next;
	return (curr);
}

void	reset_graph(t_tmp *list)
{
	t_tmp	*curr;
	t_tmp	*next;
	t_room	*out;
	t_next	*neigh_neigh;

	curr = list;
	while (curr && curr->next && !curr->next->room->out)
		curr = curr->next;
	next = NULL;
	curr = dop_2(next, curr);
	while (curr)
	{
		next = curr->next;
		out = curr->room->out;
		neigh_neigh = out->next;
		while (neigh_neigh->room != curr->room)
			neigh_neigh = neigh_neigh->next;
		neigh_neigh->room = curr->room->next->room;
		neigh_neigh->global_toggle = curr->room->next->global_toggle;
		dop_1(out, curr);
		free_(curr);
		g_lemin->edge--;
		curr = next;
	}
	dop_end(list);
}
