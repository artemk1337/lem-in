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


/* <======================================> */
/* <========== Разбиение комнат ==========> */
/* <============== Готово ================> */


#include "lemin.h"

t_room	*split_room(t_room *curr, t_tmp *list)
{
	t_next	*neigh;
	t_next	*neigh_neigh;
	t_room	*in;
	t_room	*out;

	if (curr->in || curr->out)
	{
		// НИКОГДА НЕ ДОЛЖНО СРАБАТЫВАТЬ
		ft_putstr("ERROR 1\n");
		exit(1);
	}
	// g_lemin->finish->was_here = 1;
	// Создал комнату
	list = init_tmp(list, 1, curr->name); // ft_strjoin(curr->name, "123")
	in = find_last_room(list);
	out = curr;
	out->in = in;
	in->out = out;

	// Перенес соседей
	// Перекинул связи с out на in кроме той, по которой шли
	neigh = out->next;
	// Проблема в этом while в случае прохода по последнему соседу.
	// Непонятно, почему. Предположительно, ошибка при считывании.
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

	// Создал соседа для in
	if (!(neigh = ft_memalloc(sizeof(t_next))))
		exit(1);
	g_lemin->edge++;
	neigh->weight = -1;
	neigh->toggle = 1;
	neigh->global_toggle = 1;
	neigh->next = NULL;
	neigh->room = out->prev;
	in->next = neigh;
	in->prev = out->prev;

 	// Перекинул связь на in
	neigh = out->next;
	while (neigh)
	{
		if (neigh->room == out->prev)
		{
			neigh->room = in;
			neigh->weight = 0;
		}
		neigh = neigh->next;
	}
	out->prev = in;

	in->was_here = 1;
	out->was_here = 1;
	return (in->prev);
}