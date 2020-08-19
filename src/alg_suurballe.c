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

int		dop_alg(t_tmp *list)
{
	int count_sol;
	int i;

	i = suurballe(list);
	if (i)
		save_way(i);
	else
	{
		del_sol(&(g_lemin->solution));
		g_lemin->solution = NULL;
		reset_graph(list);
	}
	count_sol = count_sols(g_lemin->solution);
	reset_minw_prev(list);
	return (count_sol);
}

void	reset_all(t_tmp *list)
{
	reset_graph(list);
	reset_minw_prev(list);
}

int		algorithm(t_tmp *list, int max_ways)
{
	int i;
	int	count_sol;

	count_sol = 0;
	if (g_lemin->solution)
	{
		del_sol(&(g_lemin->solution));
		g_lemin->solution = NULL;
	}
	while (max_ways != count_sol)
	{
		i = 0;
		while (i++ < g_lemin->edge)
			if (!bellman_ford(list, 0))
				break ;
		if (!g_lemin->finish->prev)
		{
			reset_all(list);
			return (0);
		}
		count_sol = dop_alg(list);
	}
	reset_all(list);
	return (1);
}
