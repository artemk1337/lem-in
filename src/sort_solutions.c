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

//#include "lemin.h"

typedef struct			s_solution
{
//	t_room				**arr;
	unsigned int		path_len;
	struct s_solution	*next;
}						t_solution;

void sort_solutions(t_solution **solution)
{
	t_solution *begin;
	t_solution *temp[2];
	t_solution *main_iter;
	t_solution *iter;

	if (!*solution || !(*solution)->next)
		return ;
	begin = (*solution);
	main_iter = begin->next;
	while (main_iter)
	{
		iter = begin;
		while (iter->next != main_iter)
		{
			if (iter->next->path_len > main_iter->path_len)
			{
				temp[0] = iter->next;
				iter->next = main_iter;
				temp[1] = main_iter->next;
				main_iter->next = temp[0];
			}
			iter = iter->next;
		}
		main_iter = main_iter->next;
	}
}

#include <stdlib.h>

int main()
{
	t_solution *ptr, *begin;

	begin = ptr = malloc(sizeof(*ptr));
	ptr->path_len = 8;
	ptr->next = malloc(sizeof(*ptr));
	ptr = ptr->next;
	ptr->path_len = 8;
	ptr->next = malloc(sizeof(*ptr));
	ptr = ptr->next;
	ptr->path_len = 6;
	ptr->next = malloc(sizeof(*ptr));
	ptr = ptr->next;
	ptr->path_len = 7;
	sort_solutions(&begin);
}