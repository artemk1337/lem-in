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

void	dop_main(int tmp_, int ways, t_tmp *tmp)
{
	int	max_steps;
	int	steps;

	max_steps = -1;
	while (tmp_)
	{
		tmp_ = algorithm(tmp, ways);
		steps = alg_4(0);
		if (max_steps == -1)
		{
			max_steps = steps;
		}
		else if (max_steps >= steps)
		{
			if (g_lemin->prev_solution)
				del_sol(&g_lemin->prev_solution);
			max_steps = steps;
		}
		else if (max_steps < steps)
			break ;
		g_lemin->prev_solution = g_lemin->solution;
		g_lemin->solution = NULL;
		ways++;
	}
}
