/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_solutions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:08:30 by aolen             #+#    #+#             */
/*   Updated: 2020/02/27 17:08:31 by aolen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

struct s_bandwidth
{
	unsigned int	path_num;
	unsigned int	max_len;
	unsigned int	bandwidth; // max bandwidth for max_len moves
	t_solution		*solution;
};


struct s_bandwidth	*count_solution_bandwidth(t_solution *solution)
{
	int					prev_path_len;
	struct s_bandwidth *bandwidth;

	bandwidth = ft_memalloc(sizeof(*bandwidth));
	bandwidth->bandwidth = 1;
	prev_path_len = 0;
	while (solution)
	{
		if (solution->hide)
		{
			solution = solution->next;
			continue;
		}
		if (bandwidth->path_num)
			bandwidth->bandwidth += bandwidth->path_num * (solution->path_len -
					prev_path_len) + 1;
		prev_path_len = solution->path_len;
		bandwidth->path_num++;
		bandwidth->max_len = solution->path_len > bandwidth->max_len ?
				solution->path_len : bandwidth->max_len;
		solution = solution->next;
	}
	return (bandwidth);
}

/*
** Function check_solutions
** ------------------------
** 	prev_solution: solution from previous step
**	current_solution: solution from current step
**
**	return 0 if current solution better, else 1
*/
int		check_solutions(t_solution *prev_solution, t_solution *current_solution)
{
	struct s_bandwidth	*prev_bandwidth;
	struct s_bandwidth	*curr_bandwidth;
	unsigned int		counter;

	if (!prev_solution)
		return (0);
	sort_solutions(&prev_solution);
	sort_solutions(&current_solution);
	if ((prev_bandwidth = count_solution_bandwidth(prev_solution))->bandwidth >=
		g_lemin->count)
		return (1);
	curr_bandwidth = count_solution_bandwidth(current_solution);
	counter = curr_bandwidth->max_len - prev_bandwidth->max_len;
	while (counter--)
	{
		prev_bandwidth->bandwidth += prev_bandwidth->path_num;
		if (prev_bandwidth->bandwidth > g_lemin->count)
			return (1);
	}
	return (0);
}
