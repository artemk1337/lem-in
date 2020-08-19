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
	//ft_putstr("CHECK\n");
	// Считаю длину пути
	prev = curr->prev;
	while (prev)
	{
		//ft_putstr("Room: ");
		//ft_putstr(prev->name);
		//ft_putstr((prev->in) ? "_out": "");
		//ft_putstr((prev->out) ? "_in": "");
		//ft_putstr("\n");
		if (prev == g_lemin->start)
			break ;
		len++;
		// Если перешел из комнаты in в комнату out
		if (curr->in && prev->out)
		{
			// Глоб
			//ft_putstr("1\n");
			neigh = curr->next;
			while (neigh->room != prev)
				neigh = neigh->next;
			//ft_putstr((neigh) ? "YES\n": "NO\n");
			neigh->global_toggle = 0;
			//ft_putstr("2\n");
			neigh = prev->next;
			while (neigh->room != curr)
				neigh = neigh->next;
			neigh->global_toggle = 0;
			cross_way = 1;
			//ft_putstr("3\n");
		}
		curr = prev;
		prev = curr->prev;
	}
	len++;
	if (cross_way)
		return (-1);
	return (len);
}
