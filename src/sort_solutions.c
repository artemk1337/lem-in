/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_solutions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:16:29 by aolen             #+#    #+#             */
/*   Updated: 2020/03/02 14:16:29 by aolen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			len_sol(t_solution *solution)
{
	t_solution	*begin;
	int			i;

	begin = solution;
	i = 0;
	while (begin)
	{
		i++;
		begin = begin->next;
	}
	return (i);
}

t_solution	*dop_1_sot_sol(t_solution *curr, t_solution *prev,
	t_solution *start)
{
	if (curr->path_len > curr->next->path_len)
	{
		if (!prev)
		{
			start = curr->next;
			curr->next = start->next;
			start->next = curr;
		}
		else
		{
			prev->next = curr->next;
			curr->next = prev->next->next;
			prev->next->next = curr;
		}
	}
	prev = curr;
	curr = curr->next;
	return (curr);
}

void		sort_solutions(t_solution **solution)
{
	t_solution	*prev;
	t_solution	*curr;
	t_solution	*start;
	int			i;
	int			max_i;

	if (!*solution || !(*solution)->next)
		return ;
	start = (*solution);
	curr = start;
	i = 0;
	max_i = len_sol(curr);
	while (i < max_i)
	{
		prev = NULL;
		curr = start;
		while (curr && curr->next)
		{
			curr = dop_1_sot_sol(curr, prev, start);
		}
		i++;
	}
	*solution = start;
}
