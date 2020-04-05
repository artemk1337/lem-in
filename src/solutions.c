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

static void		init_sol_dop(t_solution *tmp_s, int size, t_solution *sol)
{
	int		i;
	t_next	*neigh;
    t_room  *room;

	i = 1;
    room = g_lemin->finish;
	while (room != g_lemin->start)
	{
        if (room != g_lemin->finish && !room->path)
        {
            room->path = tmp_s->arr;
            room->idx = size - i;
        }
		neigh = room->prev->next;
		while (neigh->room != room)
			neigh = neigh->next;
		tmp_s->arr[size - i] = neigh->room;
		room = room->prev;
		i++;
	}
	tmp_s->hide = 0;
	tmp_s->arr[size - i] = g_lemin->start;
	tmp_s->arr[size - i]->idx = size - i;
	g_lemin->solution = sol;
}

void	    	init_sol(t_solution *sol, int size)
{
	t_solution	*tmp_s;

	if (!(sol))
	{
		if (!(sol = ft_memalloc(sizeof(t_solution))))
			exit(1);
		tmp_s = sol;
	}
	else
	{
		tmp_s = sol;
		while (tmp_s->next)
			tmp_s = tmp_s->next;
		if (!(tmp_s->next = ft_memalloc(sizeof(t_solution))))
			exit(1);
		tmp_s = tmp_s->next;
	}
	if (!(tmp_s->arr = malloc(sizeof(t_room *) * (size + 1))))
		exit(1);
	tmp_s->arr[size] = NULL;
	tmp_s->path_len = size;
	init_sol_dop(tmp_s, size, sol);
}

int                 save_tmp()
{
	t_room	*room;
	t_next	*neigh;
	t_next	*neigh_tmp;
	int		tmp_rooms;

	room = g_lemin->finish;
	tmp_rooms = 1;
	while (room != g_lemin->start)
	{
        if (!room)
            return (0);
		tmp_rooms++;
		neigh = room->prev->next;
		while (neigh->room != room)
			neigh = neigh->next;
		neigh->toggle = 0;
		// Change weight
		neigh_tmp = room->next;
		while (neigh_tmp->room != room->prev)
			neigh_tmp = neigh_tmp->next;
		neigh_tmp->weight = -1;
		room = room->prev;
	}
	init_sol(g_lemin->solution, tmp_rooms);
    return (1);
}

void			reset_struct(t_tmp *list)
{
	t_tmp *tmp;

	tmp = list;
	while (tmp)
	{
		tmp->room->prev = NULL;
		tmp->room->prev1 = NULL;
        if (tmp->room != g_lemin->start)
		    tmp->room->min_w = INT_MAX / 2;
		tmp = tmp->next;
	}
}

