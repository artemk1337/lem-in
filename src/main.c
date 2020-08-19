/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:04:40 by cchadwic          #+#    #+#             */
/*   Updated: 2020/03/02 15:32:02 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(void)
{
	t_tmp	*tmp;
	int		tmp_;
	int		ways;

	g_lemin = init_lemin();
	tmp = create_struct();
	g_lemin->arr = create_array(&tmp);
	check_duplicate_nodes(g_lemin->arr);
	ways = 1;
	tmp_ = 1;
	dop_main(tmp_, ways, tmp);
	if (g_lemin->solution)
		del_sol(&g_lemin->solution);
	g_lemin->solution = g_lemin->prev_solution;
	sort_solutions(&g_lemin->solution);
	if (!(g_lemin->solution))
		error_exit();
	show_input();
	alg_4(1);
	show_max_lines();
	clean_tmp(&tmp);
	return (0);
}
