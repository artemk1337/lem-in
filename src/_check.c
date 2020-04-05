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

	//ft_putstr("\n");
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

void	print_sol(void)
{
	t_solution	*sol;
	int			i;

	if (!g_lemin->solution)
	{
		ft_putstr("NO SOLUTION\n");
		return ;	
	}
	ft_putstr("Ways:\n\n");
	sol = g_lemin->solution;
	while (sol)
	{
		//ft_putstr("Solve:\n");
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

void	check_struct(t_tmp *tmp)
{
	t_next *neigh;
	
	ft_putnbr(g_lemin->count);
	ft_putstr(" count\n\n");
	
	ft_putstr("START: ");
	ft_putstr(g_lemin->start->name);
	ft_putstr("\n");
	ft_putstr("FINISH: ");
	ft_putstr(g_lemin->finish->name);
	ft_putstr("\n");
	
	while (tmp)
	{
		ft_putstr(tmp->room->name);
		ft_putstr(" room:");
		ft_putstr("\t| ");
		ft_putstr("was_here ");
		ft_putnbr((tmp->room->path) ? 1 : 0);
		ft_putstr("\t| ");
		ft_putstr("min_w ");
		ft_putnbr(tmp->room->min_w);
		ft_putstr("\t| ");
		ft_putstr("prev ");
		ft_putstr((tmp->room->prev) ? tmp->room->prev->name : "NULL");
		ft_putstr("\t| ");
		ft_putstr("pos ");
		ft_putnbr(tmp->room->superpos);
		ft_putstr("\t| ");
		ft_putstr("path ");
		(tmp->room->path) ? ft_putnbr(1) : ft_putnbr(0);
		neigh = tmp->room->next;
		while (neigh)
		{
			ft_putstr("\n\t");
			ft_putstr("next ");
			ft_putstr(neigh->room->name);
			ft_putstr("\t| ");
			ft_putstr("weight ");
			if (neigh->weight >= 0)
				ft_putstr(" ");
			ft_putnbr(neigh->weight);
			ft_putstr("\t| ");
			ft_putstr("toggle ");
			ft_putnbr(neigh->toggle);
			neigh = neigh->next;
		}
		ft_putstr("\n");
		tmp = tmp->next;
	}
}
