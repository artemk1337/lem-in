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

int		bellman_ford(t_tmp *start, int counter)
{
	t_tmp	*curr;
	t_next	*curr_n;

	counter = 0;
	curr = start;
	while (curr)
	{
		curr_n = curr->room->next;
		while (curr_n)
		{
			if (curr_n->toggle && curr_n->global_toggle
				&& curr->room->min_w + curr_n->weight < curr_n->room->min_w
				&& curr->room != g_lemin->finish &&
				curr->room->min_w != (INT_MAX / 2))
			{
				counter++;
				curr_n->room->prev = curr->room;
				curr_n->room->min_w = curr->room->min_w + curr_n->weight;
			}
			curr_n = curr_n->next;
		}
		curr = curr->next;
	}
	return (counter);
}
