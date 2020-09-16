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

int		dop_count_len_way1(t_room *prev, t_room *curr, int *len, t_next *neigh)
{
	int cross_way;

	cross_way = 0;
	while (prev)
	{
		if (prev == g_lemin->start)
			break ;
		(*len)++;
		if (curr->in && prev->out)
		{
			neigh = curr->next;
			while (neigh->room != prev)
				neigh = neigh->next;
			neigh->global_toggle = 0;
			neigh = prev->next;
			while (neigh->room != curr)
				neigh = neigh->next;
			neigh->global_toggle = 0;
			cross_way = 1;
		}
		curr = prev;
		prev = curr->prev;
	}
	return (cross_way);
}

int		count_len_way(void)
{
	t_room	*curr;
	t_room	*prev;
	t_next	*neigh;
	int		len;
	int		cross_way;

	len = 1;
	cross_way = 0;
	curr = g_lemin->finish;
	prev = curr->prev;
	neigh = NULL;
	cross_way = dop_count_len_way1(prev, curr, &len, neigh);
	len++;
	if (cross_way)
		return (-1);
	return (len);
}
