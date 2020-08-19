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


/* <=====================================> */
/* <========== Сохранение пути ==========> */
/* <=============== Готово ==============> */


t_room	**malloc_array_rooms(int len_way)
{
	t_room	**arr;

	if (!(arr = ft_memalloc(sizeof(t_room) * (len_way + 1))))
		exit(1);
	arr[len_way] = NULL;
	return (arr);
}


void	save_way(int len_way)
{
	t_solution	*solution;
	t_room		**arr_rooms;
	t_room		*curr_r;
	int			counter_len;

	counter_len = len_way;
	arr_rooms = malloc_array_rooms(len_way);
	curr_r = g_lemin->finish;
	while (curr_r->prev)
	{
		if (curr_r->out == NULL)
			arr_rooms[--counter_len] = curr_r;
		curr_r = curr_r->prev;
	}
	arr_rooms[--counter_len] = curr_r;

	solution = g_lemin->solution;
	if (!solution)
	{
		if (!(g_lemin->solution = ft_memalloc(sizeof(t_solution))))
			exit(1);
		solution = g_lemin->solution;

		solution->arr = arr_rooms;
		solution->path_len = len_way;
		solution->next = NULL;
	}
	else
	{
		while (solution->next)
			solution = solution->next;
		if (!(solution->next = ft_memalloc(sizeof(t_solution))))
			exit(1);
		solution = solution->next;

		solution->arr = arr_rooms;
		solution->path_len = len_way;
		solution->next = NULL;
	}
}


