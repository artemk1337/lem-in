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
/* <========= Удаление разбиения =========> */
/* <============== Готово ================> */


#include "lemin.h"


/* Удаляем раздвоение на всем графе, заново переносим связи и удаляем in-связь */
void	reset_graph(t_tmp *list)
{
	t_tmp	*curr;
	t_tmp	*next;
	t_room	*out;
	t_next	*neigh;
	t_next	*neigh_neigh;

	// Ищу комнату-in 
	curr = list;
	while (curr && curr->next && !curr->next->room->out)
		curr = curr->next;
	// Указатель на NULL
	next = curr->next;
	curr->next = NULL;
	// Зачищаю список и переношу связи
	curr = next;
	while (curr)
	{
		//ft_putstr("\nDELETED: ");
		//ft_putstr(curr->room->name);
		//ft_putchar('\n');

		next = curr->next; // Можно удалить
		out = curr->room->out;
		// Переношу связь с in на предыдущую комнату
		neigh_neigh = out->next;
		while (neigh_neigh->room != curr->room)
			neigh_neigh = neigh_neigh->next;
		neigh_neigh->room = curr->room->next->room;
		neigh_neigh->global_toggle = curr->room->next->global_toggle;
		// Переношу связи на out
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
		// Удаляю комнату и ее связь
		free(curr->room->next);
		free(curr->room->name);
		free(curr->room);
		free(curr);
		g_lemin->edge--;
		curr = next;
	}

	// Переключаю toggle и восстанавливаю веса связей
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

