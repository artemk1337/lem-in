/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:22:57 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/28 19:44:38 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		test_way(void)
{
	t_room *room;

	room = g_lemin->finish;
	while (room != g_lemin->start)
	{
		ft_putstr(room->name);
		ft_putstr(" <- ");
		room = room->prev;
	}
	ft_putstr(room->name);
	ft_putstr("\n");
}

void		print_sol(void)
{
	t_solution	*sol;
	int			i;

	if (!g_lemin->solution)
	{
		ft_putstr("NO SOLUTION\n");
		return ;
	}
	ft_putstr("\nWays:\n");
	sol = g_lemin->solution;
	while (sol)
	{
		i = 0;
		while (sol->arr[i])
		{
			ft_putstr(sol->arr[i]->name);
			if (sol->arr[i + 1])
				ft_putstr(" -> ");
			i++;
		}
		ft_putchar('\n');
		sol = sol->next;
	}
	ft_putchar('\n');
}
